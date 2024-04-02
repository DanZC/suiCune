#include "../../constants.h"

const struct BuenaPassword BuenasPasswordTable[] = {
    {BUENA_MON,    10, .mon= {{CYNDAQUIL, TOTODILE, CHIKORITA}}}, // JohtoStarters
    {BUENA_ITEM,   12, .item={{FRESH_WATER, SODA_POP, LEMONADE}}}, // Beverages
    {BUENA_ITEM,   12, .item={{POTION, ANTIDOTE, PARLYZ_HEAL}}}, // HealingItems
    {BUENA_ITEM,   12, .item={{POKE_BALL, GREAT_BALL, ULTRA_BALL}}}, // Balls
    {BUENA_MON,    10, .mon= {{PIKACHU, RATTATA, GEODUDE}}}, // Pokemon1
    {BUENA_MON,    10, .mon= {{HOOTHOOT, SPINARAK, DROWZEE}}}, // Pokemon2
    {BUENA_STRING, 16, .str= {{"NEW BARK TOWN@", "CHERRYGROVE CITY@", "AZALEA TOWN@"}}}, // JohtoTowns
    {BUENA_STRING,  6, .str= {{"FLYING@", "BUG@", "GRASS@"}}}, // Types
    {BUENA_MOVE,   12, .move={{TACKLE, GROWL, MUD_SLAP}}}, // Moves
    {BUENA_ITEM,   12, .item={{X_ATTACK, X_DEFEND, X_SPEED}}}, // XItems
    {BUENA_STRING, 13, .str= {{"#MON Talk@", "#MON Music@", "Lucky Channel@"}}}, // RadioStations
};
