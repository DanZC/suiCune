#include "../../constants.h"
#include "outdoor_sprites.h"

static const uint8_t PalletGroupSprites[] = {
    SPRITE_SUICUNE,
    SPRITE_SILVER_TROPHY,
    SPRITE_FAMICOM,
    SPRITE_POKEDEX,
    SPRITE_WILL,
    SPRITE_KAREN,
    SPRITE_NURSE,
    SPRITE_OLD_LINK_RECEPTIONIST,
    SPRITE_BIG_LAPRAS,
    SPRITE_BIG_ONIX,
    SPRITE_SUDOWOODO,
    SPRITE_BIG_SNORLAX,
    SPRITE_TEACHER,
    SPRITE_FISHER,
    SPRITE_YOUNGSTER,
    SPRITE_BLUE,
    SPRITE_GRAMPS,
    SPRITE_BUG_CATCHER,
    SPRITE_COOLTRAINER_F,
    SPRITE_SWIMMER_GIRL,
    SPRITE_SWIMMER_GUY,
    SPRITE_POKE_BALL,
    SPRITE_FRUIT_TREE,
};

static const uint8_t ViridianGroupSprites[] = {
    SPRITE_SUICUNE,
    SPRITE_SILVER_TROPHY,
    SPRITE_FAMICOM,
    SPRITE_POKEDEX,
    SPRITE_WILL,
    SPRITE_KAREN,
    SPRITE_NURSE,
    SPRITE_OLD_LINK_RECEPTIONIST,
    SPRITE_BIG_LAPRAS,
    SPRITE_BIG_ONIX,
    SPRITE_SUDOWOODO,
    SPRITE_BIG_SNORLAX,
    SPRITE_TEACHER,
    SPRITE_FISHER,
    SPRITE_YOUNGSTER,
    SPRITE_BLUE,
    SPRITE_GRAMPS,
    SPRITE_BUG_CATCHER,
    SPRITE_COOLTRAINER_F,
    SPRITE_SWIMMER_GIRL,
    SPRITE_SWIMMER_GUY,
    SPRITE_POKE_BALL,
    SPRITE_FRUIT_TREE,
};

static const uint8_t PewterGroupSprites[] = {
    SPRITE_SUICUNE,
    SPRITE_SILVER_TROPHY,
    SPRITE_FAMICOM,
    SPRITE_POKEDEX,
    SPRITE_WILL,
    SPRITE_KAREN,
    SPRITE_NURSE,
    SPRITE_OLD_LINK_RECEPTIONIST,
    SPRITE_BIG_LAPRAS,
    SPRITE_BIG_ONIX,
    SPRITE_SUDOWOODO,
    SPRITE_BIG_SNORLAX,
    SPRITE_TEACHER,
    SPRITE_FISHER,
    SPRITE_YOUNGSTER,
    SPRITE_BLUE,
    SPRITE_GRAMPS,
    SPRITE_BUG_CATCHER,
    SPRITE_COOLTRAINER_F,
    SPRITE_SWIMMER_GIRL,
    SPRITE_SWIMMER_GUY,
    SPRITE_POKE_BALL,
    SPRITE_FRUIT_TREE,
};

static const uint8_t CinnabarGroupSprites[] = {
    SPRITE_SUICUNE,
    SPRITE_SILVER_TROPHY,
    SPRITE_FAMICOM,
    SPRITE_POKEDEX,
    SPRITE_WILL,
    SPRITE_KAREN,
    SPRITE_NURSE,
    SPRITE_OLD_LINK_RECEPTIONIST,
    SPRITE_BIG_LAPRAS,
    SPRITE_BIG_ONIX,
    SPRITE_SUDOWOODO,
    SPRITE_BIG_SNORLAX,
    SPRITE_TEACHER,
    SPRITE_FISHER,
    SPRITE_YOUNGSTER,
    SPRITE_BLUE,
    SPRITE_GRAMPS,
    SPRITE_BUG_CATCHER,
    SPRITE_COOLTRAINER_F,
    SPRITE_SWIMMER_GIRL,
    SPRITE_SWIMMER_GUY,
    SPRITE_POKE_BALL,
    SPRITE_FRUIT_TREE,
};

static const uint8_t CeruleanGroupSprites[] = {
    SPRITE_SUICUNE,
    SPRITE_SILVER_TROPHY,
    SPRITE_FAMICOM,
    SPRITE_POKEDEX,
    SPRITE_WILL,
    SPRITE_KAREN,
    SPRITE_NURSE,
    SPRITE_OLD_LINK_RECEPTIONIST,
    SPRITE_BIG_LAPRAS,
    SPRITE_BIG_ONIX,
    SPRITE_SUDOWOODO,
    SPRITE_BIG_SNORLAX,
    SPRITE_COOLTRAINER_M,
    SPRITE_SUPER_NERD,
    SPRITE_COOLTRAINER_F,
    SPRITE_FISHER,
    SPRITE_YOUNGSTER,
    SPRITE_LASS,
    SPRITE_POKEFAN_M,
    SPRITE_ROCKET,
    SPRITE_MISTY,
    SPRITE_POKE_BALL,
    SPRITE_SLOWPOKE,
};

static const uint8_t SaffronGroupSprites[] = {
    SPRITE_SUICUNE,
    SPRITE_SILVER_TROPHY,
    SPRITE_FAMICOM,
    SPRITE_POKEDEX,
    SPRITE_WILL,
    SPRITE_KAREN,
    SPRITE_NURSE,
    SPRITE_OLD_LINK_RECEPTIONIST,
    SPRITE_BIG_LAPRAS,
    SPRITE_BIG_ONIX,
    SPRITE_SUDOWOODO,
    SPRITE_BIG_SNORLAX,
    SPRITE_COOLTRAINER_M,
    SPRITE_SUPER_NERD,
    SPRITE_COOLTRAINER_F,
    SPRITE_FISHER,
    SPRITE_YOUNGSTER,
    SPRITE_LASS,
    SPRITE_POKEFAN_M,
    SPRITE_ROCKET,
    SPRITE_MISTY,
    SPRITE_POKE_BALL,
    SPRITE_SLOWPOKE,
};

static const uint8_t CeladonGroupSprites[] = {
    SPRITE_SUICUNE,
    SPRITE_SILVER_TROPHY,
    SPRITE_FAMICOM,
    SPRITE_POKEDEX,
    SPRITE_WILL,
    SPRITE_KAREN,
    SPRITE_NURSE,
    SPRITE_OLD_LINK_RECEPTIONIST,
    SPRITE_BIG_LAPRAS,
    SPRITE_BIG_ONIX,
    SPRITE_SUDOWOODO,
    SPRITE_BIG_SNORLAX,
    SPRITE_FISHER,
    SPRITE_POLIWAG,
    SPRITE_TEACHER,
    SPRITE_GRAMPS,
    SPRITE_YOUNGSTER,
    SPRITE_LASS,
    SPRITE_BIKER,
    SPRITE_SILVER,
    SPRITE_BLUE,
    SPRITE_POKE_BALL,
    SPRITE_FRUIT_TREE,
};

static const uint8_t LavenderGroupSprites[] = {
    SPRITE_SUICUNE,
    SPRITE_SILVER_TROPHY,
    SPRITE_FAMICOM,
    SPRITE_POKEDEX,
    SPRITE_WILL,
    SPRITE_KAREN,
    SPRITE_NURSE,
    SPRITE_OLD_LINK_RECEPTIONIST,
    SPRITE_BIG_LAPRAS,
    SPRITE_BIG_ONIX,
    SPRITE_SUDOWOODO,
    SPRITE_BIG_SNORLAX,
    SPRITE_POKEFAN_M,
    SPRITE_MACHOP,
    SPRITE_GRAMPS,
    SPRITE_YOUNGSTER,
    SPRITE_FISHER,
    SPRITE_TEACHER,
    SPRITE_SUPER_NERD,
    SPRITE_BIG_SNORLAX,
    SPRITE_BIKER,
    SPRITE_POKE_BALL,
    SPRITE_FRUIT_TREE,
};

static const uint8_t VermilionGroupSprites[] = {
    SPRITE_SUICUNE,
    SPRITE_SILVER_TROPHY,
    SPRITE_FAMICOM,
    SPRITE_POKEDEX,
    SPRITE_WILL,
    SPRITE_KAREN,
    SPRITE_NURSE,
    SPRITE_OLD_LINK_RECEPTIONIST,
    SPRITE_BIG_LAPRAS,
    SPRITE_BIG_ONIX,
    SPRITE_SUDOWOODO,
    SPRITE_BIG_SNORLAX,
    SPRITE_POKEFAN_M,
    SPRITE_MACHOP,
    SPRITE_GRAMPS,
    SPRITE_YOUNGSTER,
    SPRITE_FISHER,
    SPRITE_TEACHER,
    SPRITE_SUPER_NERD,
    SPRITE_BIG_SNORLAX,
    SPRITE_BIKER,
    SPRITE_POKE_BALL,
    SPRITE_FRUIT_TREE,
};

static const uint8_t FuchsiaGroupSprites[] = {
    SPRITE_SUICUNE,
    SPRITE_SILVER_TROPHY,
    SPRITE_FAMICOM,
    SPRITE_POKEDEX,
    SPRITE_WILL,
    SPRITE_KAREN,
    SPRITE_NURSE,
    SPRITE_OLD_LINK_RECEPTIONIST,
    SPRITE_BIG_LAPRAS,
    SPRITE_BIG_ONIX,
    SPRITE_SUDOWOODO,
    SPRITE_BIG_SNORLAX,
    SPRITE_POKEFAN_M,
    SPRITE_MACHOP,
    SPRITE_GRAMPS,
    SPRITE_YOUNGSTER,
    SPRITE_FISHER,
    SPRITE_TEACHER,
    SPRITE_SUPER_NERD,
    SPRITE_BIG_SNORLAX,
    SPRITE_BIKER,
    SPRITE_POKE_BALL,
    SPRITE_FRUIT_TREE,
};

static const uint8_t IndigoGroupSprites[] = {
    SPRITE_SUICUNE,
    SPRITE_SILVER_TROPHY,
    SPRITE_FAMICOM,
    SPRITE_POKEDEX,
    SPRITE_WILL,
    SPRITE_KAREN,
    SPRITE_NURSE,
    SPRITE_OLD_LINK_RECEPTIONIST,
    SPRITE_BIG_LAPRAS,
    SPRITE_BIG_ONIX,
    SPRITE_SUDOWOODO,
    SPRITE_BIG_SNORLAX,
    SPRITE_POKEFAN_M,
    SPRITE_BEAUTY,
    SPRITE_GRAMPS,
    SPRITE_YOUNGSTER,
    SPRITE_FISHER,
    SPRITE_TEACHER,
    SPRITE_SUPER_NERD,
    SPRITE_MACHOP,
    SPRITE_BIKER,
    SPRITE_POKE_BALL,
    SPRITE_BOULDER,
};

static const uint8_t NewBarkGroupSprites[] = {
    SPRITE_SUICUNE,
    SPRITE_SILVER_TROPHY,
    SPRITE_FAMICOM,
    SPRITE_POKEDEX,
    SPRITE_WILL,
    SPRITE_KAREN,
    SPRITE_NURSE,
    SPRITE_OLD_LINK_RECEPTIONIST,
    SPRITE_BIG_LAPRAS,
    SPRITE_BIG_ONIX,
    SPRITE_SUDOWOODO,
    SPRITE_BIG_SNORLAX,
    SPRITE_SILVER,
    SPRITE_TEACHER,
    SPRITE_FISHER,
    SPRITE_COOLTRAINER_M,
    SPRITE_YOUNGSTER,
    SPRITE_MONSTER,
    SPRITE_GRAMPS,
    SPRITE_BUG_CATCHER,
    SPRITE_COOLTRAINER_F,
    SPRITE_POKE_BALL,
    SPRITE_FRUIT_TREE,
};

static const uint8_t CherrygroveGroupSprites[] = {
    SPRITE_SUICUNE,
    SPRITE_SILVER_TROPHY,
    SPRITE_FAMICOM,
    SPRITE_POKEDEX,
    SPRITE_WILL,
    SPRITE_KAREN,
    SPRITE_NURSE,
    SPRITE_OLD_LINK_RECEPTIONIST,
    SPRITE_BIG_LAPRAS,
    SPRITE_BIG_ONIX,
    SPRITE_SUDOWOODO,
    SPRITE_BIG_SNORLAX,
    SPRITE_SILVER,
    SPRITE_TEACHER,
    SPRITE_FISHER,
    SPRITE_COOLTRAINER_M,
    SPRITE_YOUNGSTER,
    SPRITE_MONSTER,
    SPRITE_GRAMPS,
    SPRITE_BUG_CATCHER,
    SPRITE_COOLTRAINER_F,
    SPRITE_POKE_BALL,
    SPRITE_FRUIT_TREE,
};

static const uint8_t SilverGroupSprites[] = {
    SPRITE_SUICUNE,
    SPRITE_SILVER_TROPHY,
    SPRITE_FAMICOM,
    SPRITE_POKEDEX,
    SPRITE_WILL,
    SPRITE_KAREN,
    SPRITE_NURSE,
    SPRITE_OLD_LINK_RECEPTIONIST,
    SPRITE_BIG_LAPRAS,
    SPRITE_BIG_ONIX,
    SPRITE_SUDOWOODO,
    SPRITE_BIG_SNORLAX,
    SPRITE_SILVER,
    SPRITE_TEACHER,
    SPRITE_FISHER,
    SPRITE_COOLTRAINER_M,
    SPRITE_YOUNGSTER,
    SPRITE_MONSTER,
    SPRITE_GRAMPS,
    SPRITE_BUG_CATCHER,
    SPRITE_COOLTRAINER_F,
    SPRITE_POKE_BALL,
    SPRITE_FRUIT_TREE,
};

static const uint8_t VioletGroupSprites[] = {
    SPRITE_SUICUNE,
    SPRITE_SILVER_TROPHY,
    SPRITE_FAMICOM,
    SPRITE_POKEDEX,
    SPRITE_WILL,
    SPRITE_KAREN,
    SPRITE_NURSE,
    SPRITE_OLD_LINK_RECEPTIONIST,
    SPRITE_BIG_LAPRAS,
    SPRITE_BIG_ONIX,
    SPRITE_SUDOWOODO,
    SPRITE_BIG_SNORLAX,
    SPRITE_FISHER,
    SPRITE_LASS,
    SPRITE_OFFICER,
    SPRITE_GRAMPS,
    SPRITE_YOUNGSTER,
    SPRITE_COOLTRAINER_M,
    SPRITE_BUG_CATCHER,
    SPRITE_SUPER_NERD,
    SPRITE_WEIRD_TREE,
    SPRITE_POKE_BALL,
    SPRITE_FRUIT_TREE,
};

static const uint8_t EcruteakGroupSprites[] = {
    SPRITE_SUICUNE,
    SPRITE_SILVER_TROPHY,
    SPRITE_FAMICOM,
    SPRITE_POKEDEX,
    SPRITE_WILL,
    SPRITE_KAREN,
    SPRITE_NURSE,
    SPRITE_OLD_LINK_RECEPTIONIST,
    SPRITE_BIG_LAPRAS,
    SPRITE_BIG_ONIX,
    SPRITE_SUDOWOODO,
    SPRITE_BIG_SNORLAX,
    SPRITE_FISHER,
    SPRITE_LASS,
    SPRITE_OFFICER,
    SPRITE_GRAMPS,
    SPRITE_YOUNGSTER,
    SPRITE_COOLTRAINER_M,
    SPRITE_BUG_CATCHER,
    SPRITE_SUPER_NERD,
    SPRITE_WEIRD_TREE,
    SPRITE_POKE_BALL,
    SPRITE_FRUIT_TREE,
};

static const uint8_t AzaleaGroupSprites[] = {
    SPRITE_SUICUNE,
    SPRITE_SILVER_TROPHY,
    SPRITE_FAMICOM,
    SPRITE_POKEDEX,
    SPRITE_WILL,
    SPRITE_KAREN,
    SPRITE_NURSE,
    SPRITE_OLD_LINK_RECEPTIONIST,
    SPRITE_KURT_OUTSIDE,
    SPRITE_BIG_ONIX,
    SPRITE_SUDOWOODO,
    SPRITE_BIG_SNORLAX,
    SPRITE_GRAMPS,
    SPRITE_YOUNGSTER,
    SPRITE_OFFICER,
    SPRITE_POKEFAN_M,
    SPRITE_BLACK_BELT,
    SPRITE_TEACHER,
    SPRITE_AZALEA_ROCKET,
    SPRITE_LASS,
    SPRITE_SILVER,
    SPRITE_FRUIT_TREE,
    SPRITE_SLOWPOKE,
};

static const uint8_t GoldenrodGroupSprites[] = {
    SPRITE_SUICUNE,
    SPRITE_SILVER_TROPHY,
    SPRITE_POKE_BALL,
    SPRITE_POKEDEX,
    SPRITE_WILL,
    SPRITE_KAREN,
    SPRITE_NURSE,
    SPRITE_OLD_LINK_RECEPTIONIST,
    SPRITE_BIG_LAPRAS,
    SPRITE_BIG_ONIX,
    SPRITE_SUDOWOODO,
    SPRITE_BIG_SNORLAX,
    SPRITE_GRAMPS,
    SPRITE_YOUNGSTER,
    SPRITE_OFFICER,
    SPRITE_POKEFAN_M,
    SPRITE_DAY_CARE_MON_1,
    SPRITE_COOLTRAINER_F,
    SPRITE_ROCKET,
    SPRITE_LASS,
    SPRITE_DAY_CARE_MON_2,
    SPRITE_FRUIT_TREE,
    SPRITE_SLOWPOKE,
};

static const uint8_t CianwoodGroupSprites[] = {
    SPRITE_SUICUNE,
    SPRITE_SILVER_TROPHY,
    SPRITE_FAMICOM,
    SPRITE_POKEDEX,
    SPRITE_WILL,
    SPRITE_KAREN,
    SPRITE_NURSE,
    SPRITE_OLD_LINK_RECEPTIONIST,
    SPRITE_STANDING_YOUNGSTER,
    SPRITE_BIG_ONIX,
    SPRITE_SUDOWOODO,
    SPRITE_BIG_SNORLAX,
    SPRITE_OLIVINE_RIVAL,
    SPRITE_POKEFAN_M,
    SPRITE_LASS,
    SPRITE_BEAUTY,
    SPRITE_SWIMMER_GIRL,
    SPRITE_SAILOR,
    SPRITE_POKEFAN_F,
    SPRITE_SUPER_NERD,
    SPRITE_TAUROS,
    SPRITE_FRUIT_TREE,
    SPRITE_ROCK,
};

static const uint8_t OlivineGroupSprites[] = {
    SPRITE_SUICUNE,
    SPRITE_SILVER_TROPHY,
    SPRITE_FAMICOM,
    SPRITE_POKEDEX,
    SPRITE_WILL,
    SPRITE_KAREN,
    SPRITE_NURSE,
    SPRITE_OLD_LINK_RECEPTIONIST,
    SPRITE_STANDING_YOUNGSTER,
    SPRITE_BIG_ONIX,
    SPRITE_SUDOWOODO,
    SPRITE_BIG_SNORLAX,
    SPRITE_OLIVINE_RIVAL,
    SPRITE_POKEFAN_M,
    SPRITE_LASS,
    SPRITE_BEAUTY,
    SPRITE_SWIMMER_GIRL,
    SPRITE_SAILOR,
    SPRITE_POKEFAN_F,
    SPRITE_SUPER_NERD,
    SPRITE_TAUROS,
    SPRITE_FRUIT_TREE,
    SPRITE_ROCK,
};

static const uint8_t LakeOfRageGroupSprites[] = {
    SPRITE_SUICUNE,
    SPRITE_SILVER_TROPHY,
    SPRITE_FAMICOM,
    SPRITE_POKEDEX,
    SPRITE_WILL,
    SPRITE_KAREN,
    SPRITE_NURSE,
    SPRITE_OLD_LINK_RECEPTIONIST,
    SPRITE_BIG_LAPRAS,
    SPRITE_BIG_ONIX,
    SPRITE_SUDOWOODO,
    SPRITE_BIG_SNORLAX,
    SPRITE_LANCE,
    SPRITE_GRAMPS,
    SPRITE_SUPER_NERD,
    SPRITE_COOLTRAINER_F,
    SPRITE_FISHER,
    SPRITE_COOLTRAINER_M,
    SPRITE_LASS,
    SPRITE_YOUNGSTER,
    SPRITE_GYARADOS,
    SPRITE_FRUIT_TREE,
    SPRITE_POKE_BALL,
};

static const uint8_t MahoganyGroupSprites[] = {
    SPRITE_SUICUNE,
    SPRITE_SILVER_TROPHY,
    SPRITE_FAMICOM,
    SPRITE_POKEDEX,
    SPRITE_WILL,
    SPRITE_KAREN,
    SPRITE_NURSE,
    SPRITE_OLD_LINK_RECEPTIONIST,
    SPRITE_BIG_LAPRAS,
    SPRITE_BIG_ONIX,
    SPRITE_SUDOWOODO,
    SPRITE_BIG_SNORLAX,
    SPRITE_GRAMPS,
    SPRITE_YOUNGSTER,
    SPRITE_LASS,
    SPRITE_SUPER_NERD,
    SPRITE_COOLTRAINER_M,
    SPRITE_POKEFAN_M,
    SPRITE_BLACK_BELT,
    SPRITE_COOLTRAINER_F,
    SPRITE_FISHER,
    SPRITE_FRUIT_TREE,
    SPRITE_POKE_BALL,
};

static const uint8_t BlackthornGroupSprites[] = {
    SPRITE_SUICUNE,
    SPRITE_SILVER_TROPHY,
    SPRITE_FAMICOM,
    SPRITE_POKEDEX,
    SPRITE_WILL,
    SPRITE_KAREN,
    SPRITE_NURSE,
    SPRITE_OLD_LINK_RECEPTIONIST,
    SPRITE_BIG_LAPRAS,
    SPRITE_BIG_ONIX,
    SPRITE_SUDOWOODO,
    SPRITE_BIG_SNORLAX,
    SPRITE_GRAMPS,
    SPRITE_YOUNGSTER,
    SPRITE_LASS,
    SPRITE_SUPER_NERD,
    SPRITE_COOLTRAINER_M,
    SPRITE_POKEFAN_M,
    SPRITE_BLACK_BELT,
    SPRITE_COOLTRAINER_F,
    SPRITE_FISHER,
    SPRITE_FRUIT_TREE,
    SPRITE_POKE_BALL,
};

static const uint8_t DungeonsGroupSprites[] = {
    SPRITE_SUICUNE,
    SPRITE_SILVER_TROPHY,
    SPRITE_FAMICOM,
    SPRITE_POKEDEX,
    SPRITE_WILL,
    SPRITE_KAREN,
    SPRITE_NURSE,
    SPRITE_OLD_LINK_RECEPTIONIST,
    SPRITE_GAMEBOY_KID,
    SPRITE_BIG_ONIX,
    SPRITE_SUDOWOODO,
    SPRITE_BIG_SNORLAX,
    SPRITE_LASS,
    SPRITE_POKEFAN_F,
    SPRITE_TEACHER,
    SPRITE_YOUNGSTER,
    SPRITE_GROWLITHE,
    SPRITE_POKEFAN_M,
    SPRITE_ROCKER,
    SPRITE_FISHER,
    SPRITE_SCIENTIST,
    SPRITE_POKE_BALL,
    SPRITE_BOULDER,
};

static const uint8_t FastShipGroupSprites[] = {
    SPRITE_SUICUNE,
    SPRITE_SILVER_TROPHY,
    SPRITE_FAMICOM,
    SPRITE_POKEDEX,
    SPRITE_WILL,
    SPRITE_KAREN,
    SPRITE_NURSE,
    SPRITE_OLD_LINK_RECEPTIONIST,
    SPRITE_BIG_LAPRAS,
    SPRITE_BIG_ONIX,
    SPRITE_SUDOWOODO,
    SPRITE_BIG_SNORLAX,
    SPRITE_SAILOR,
    SPRITE_FISHING_GURU,
    SPRITE_GENTLEMAN,
    SPRITE_SUPER_NERD,
    SPRITE_HO_OH,
    SPRITE_TEACHER,
    SPRITE_COOLTRAINER_F,
    SPRITE_YOUNGSTER,
    SPRITE_FAIRY,
    SPRITE_POKE_BALL,
    SPRITE_ROCK,
};

static const uint8_t CableClubGroupSprites[] = {
    SPRITE_OAK,
    SPRITE_FISHER,
    SPRITE_TEACHER,
    SPRITE_TWIN,
    SPRITE_POKEFAN_M,
    SPRITE_GRAMPS,
    SPRITE_FAIRY,
    SPRITE_SILVER,
    SPRITE_FISHING_GURU,
    SPRITE_POKE_BALL,
    SPRITE_POKEDEX,
};


// Valid sprite IDs for each map group.
// Maps with environment ROUTE or TOWN can only use these sprites.
const uint8_t* OutdoorSprites[] = {
// entries correspond to MAPGROUP_* constants
    OlivineGroupSprites,
    MahoganyGroupSprites,
    DungeonsGroupSprites,
    EcruteakGroupSprites,
    BlackthornGroupSprites,
    CinnabarGroupSprites,
    CeruleanGroupSprites,
    AzaleaGroupSprites,
    LakeOfRageGroupSprites,
    VioletGroupSprites,
    GoldenrodGroupSprites,
    VermilionGroupSprites,
    PalletGroupSprites,
    PewterGroupSprites,
    FastShipGroupSprites,
    IndigoGroupSprites,
    FuchsiaGroupSprites,
    LavenderGroupSprites,
    SilverGroupSprites,
    CableClubGroupSprites,
    CeladonGroupSprites,
    CianwoodGroupSprites,
    ViridianGroupSprites,
    NewBarkGroupSprites,
    SaffronGroupSprites,
    CherrygroveGroupSprites,
};
static_assert(lengthof(OutdoorSprites) == NUM_MAP_GROUPS, "");
