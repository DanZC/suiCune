#include "../../constants.h"

enum {
    MOM_ITEM = 1,
	MOM_DOLL
};

struct MomPhoneItem {
    uint32_t moneyToTrigger;
    uint32_t cost;
    uint8_t kind;
    uint8_t item;
};

const struct MomPhoneItem MomItems_1[] = {
    {      0,   600, MOM_ITEM, SUPER_POTION},
    {      0,    90, MOM_ITEM, ANTIDOTE},
    {      0,   180, MOM_ITEM, POKE_BALL},
    {      0,   450, MOM_ITEM, ESCAPE_ROPE},
    {      0,   500, MOM_ITEM, GREAT_BALL},
};

const struct MomPhoneItem MomItems_2[] = {
    {    900,   600, MOM_ITEM, SUPER_POTION},
    {   4000,   270, MOM_ITEM, REPEL},
    {   7000,   600, MOM_ITEM, SUPER_POTION},
    {  10000,  1800, MOM_DOLL, DECO_CHARMANDER_DOLL},
    {  15000,  3000, MOM_ITEM, MOON_STONE},
    {  19000,   600, MOM_ITEM, SUPER_POTION},
    {  30000,  4800, MOM_DOLL, DECO_CLEFAIRY_DOLL},
    {  40000,   900, MOM_ITEM, HYPER_POTION},
    {  50000,  8000, MOM_DOLL, DECO_PIKACHU_DOLL},
    { 100000, 22800, MOM_DOLL, DECO_BIG_SNORLAX_DOLL},
};