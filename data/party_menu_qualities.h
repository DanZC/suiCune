#pragma once

// WritePartyMenuTilemap.Jumptable indexes (see engine/pokemon/party_menu.asm)
enum {
    PARTYMENUQUALITY_NICKNAMES,
    PARTYMENUQUALITY_HP_BAR,
    PARTYMENUQUALITY_HP_DIGITS,
    PARTYMENUQUALITY_LEVEL,
    PARTYMENUQUALITY_STATUS,
    PARTYMENUQUALITY_TMHM_COMPAT,
    PARTYMENUQUALITY_EVO_STONE_COMPAT,
    PARTYMENUQUALITY_GENDER,
    PARTYMENUQUALITY_MOBILE_SELECTION,
};

extern const uint8_t* const PartyMenuQualityPointers[];