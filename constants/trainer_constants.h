
// trainer class ids
// `trainerclass` indexes are for:
// - TrainerClassNames (see data/trainers/class_names.asm)
// - TrainerClassAttributes (see data/trainers/attributes.asm)
// - TrainerClassDVs (see data/trainers/dvs.asm)
// - TrainerGroups (see data/trainers/party_pointers.asm)
// - TrainerEncounterMusic (see data/trainers/encounter_music.asm)
// - TrainerPicPointers (see data/trainers/pic_pointers.asm)
// - TrainerPalettes (see data/trainers/palettes.asm)
// - BTTrainerClassSprites (see data/trainers/sprites.asm)
// - BTTrainerClassGenders (see data/trainers/genders.asm)
// trainer constants are Trainers indexes, for the sub-tables of TrainerGroups (see data/trainers/parties.asm)
#define CHRIS 0
#define KRIS 1

#define TRAINER_NONE 0x00
enum {
    PHONECONTACT_MOM = 1,
    PHONECONTACT_BIKESHOP,
    PHONECONTACT_BILL,
    PHONECONTACT_ELM,
    PHONECONTACT_BUENA,
};

#define NUM_NONTRAINER_PHONECONTACTS PHONECONTACT_BUENA

#define FALKNER 0x01
enum {
    FALKNER1,
};

#define WHITNEY 0x02
enum {
    WHITNEY1,
};

#define BUGSY 0x03
enum {
    BUGSY1,
};

#define MORTY 0x04
enum {
    MORTY1,
};

#define PRYCE 0x05
enum {
    PRYCE1,
};

#define JASMINE 0x06
enum {
    JASMINE1,
};

#define CHUCK 0x07
enum {
    CHUCK1,
};

#define CLAIR 0x08
enum {
    CLAIR1,
};

#define RIVAL1 0x09
enum {
    RIVAL1_1_CHIKORITA,
    RIVAL1_1_CYNDAQUIL,
    RIVAL1_1_TOTODILE,
    RIVAL1_2_CHIKORITA,
    RIVAL1_2_CYNDAQUIL,
    RIVAL1_2_TOTODILE,
    RIVAL1_3_CHIKORITA,
    RIVAL1_3_CYNDAQUIL,
    RIVAL1_3_TOTODILE,
    RIVAL1_4_CHIKORITA,
    RIVAL1_4_CYNDAQUIL,
    RIVAL1_4_TOTODILE,
    RIVAL1_5_CHIKORITA,
    RIVAL1_5_CYNDAQUIL,
    RIVAL1_5_TOTODILE,
};

#define POKEMON_PROF 0x0a

#define WILL 0x0b
enum {
    WILL1,
};

#define CAL 0x0c
enum {
    CAL1,  // unused
    CAL2,
    CAL3,
};

#define BRUNO 0x0d
enum {
    BRUNO1,
};

#define KAREN 0x0e
enum {
    KAREN1,
};

#define KOGA 0x0f
enum {
    KOGA1,
};

#define CHAMPION 0x10
enum {
    LANCE,
};

#define BROCK 0x11
enum {
    BROCK1,
};

#define MISTY 0x12
enum {
    MISTY1,
};

#define LT_SURGE 0x13
enum {
    LT_SURGE1,
};

#define SCIENTIST 0x14
enum {
    ROSS,
    MITCH,
    JED,
    MARC,
    RICH,
};

#define ERIKA 0x15
enum {
    ERIKA1,
};

#define YOUNGSTER 0x16
enum {
    JOEY1,
    MIKEY,
    ALBERT,
    GORDON,
    SAMUEL,
    IAN,
    JOEY2,
    JOEY3,
    WARREN,
    JIMMY,
    OWEN,
    JASON,
    JOEY4,
    JOEY5,
};

#define SCHOOLBOY 0x17
enum {
    JACK1,
    KIPP,
    ALAN1,
    JOHNNY,
    DANNY,
    TOMMY,
    DUDLEY,
    JOE,
    BILLY,
    CHAD1,
    NATE,
    RICKY,
    JACK2,
    JACK3,
    ALAN2,
    ALAN3,
    CHAD2,
    CHAD3,
    JACK4,
    JACK5,
    ALAN4,
    ALAN5,
    CHAD4,
    CHAD5,
};

#define BIRD_KEEPER 0x18
enum {
    ROD,
    ABE,
    BRYAN,
    THEO,
    TOBY,
    DENIS,
    VANCE1,
    HANK,
    ROY,
    BORIS,
    BOB,
    JOSE1,
    PETER,
    JOSE2,
    PERRY,
    BRET,
    JOSE3,
    VANCE2,
    VANCE3,
};

#define LASS 0x19
enum {
    CARRIE,
    BRIDGET,
    ALICE,
    KRISE,
    CONNIE1,
    LINDA,
    LAURA,
    SHANNON,
    MICHELLE,
    DANA1,
    ELLEN,
    CONNIE2,  // unused
    CONNIE3,  // unused
    DANA2,
    DANA3,
    DANA4,
    DANA5,
};

#define JANINE 0x1a
enum {
    JANINE1,
};

#define COOLTRAINERM 0x1b
enum {
    NICK,
    AARON,
    PAUL,
    CODY,
    MIKE,
    GAVEN1,
    GAVEN2,
    RYAN,
    JAKE,
    GAVEN3,
    BLAKE,
    BRIAN,
    ERICK,  // unused
    ANDY,   // unused
    TYLER,  // unused
    SEAN,
    KEVIN,
    STEVE,  // unused
    ALLEN,
    DARIN,
};

#define COOLTRAINERF 0x1c
enum {
    GWEN,
    LOIS,
    FRAN,
    LOLA,
    KATE,
    IRENE,
    KELLY,
    JOYCE,
    BETH1,
    REENA1,
    MEGAN,
    BETH2,
    CAROL,
    QUINN,
    EMMA,
    CYBIL,
    JENN,
    BETH3,
    REENA2,
    REENA3,
    CARA,
};

#define BEAUTY 0x1d
enum {
    VICTORIA,
    SAMANTHA,
    JULIE,   // unused
    JACLYN,  // unused
    BRENDA,  // unused
    CASSIE,
    CAROLINE,  // unused
    CARLENE,   // unused
    JESSICA,   // unused
    RACHAEL,   // unused
    ANGELICA,  // unused
    KENDRA,    // unused
    VERONICA,  // unused
    JULIA,
    THERESA,  // unused
    VALERIE,
    OLIVIA,
};

#define POKEMANIAC 0x1e
enum {
    LARRY,
    ANDREW,
    CALVIN,
    SHANE,
    BEN,
    BRENT1,
    RON,
    ETHAN,
    BRENT2,
    BRENT3,
    ISSAC,
    DONALD,
    ZACH,
    BRENT4,
    MILLER,
};

#define GRUNTM 0x1f
enum {
    GRUNTM_1,
    GRUNTM_2,
    GRUNTM_3,
    GRUNTM_4,
    GRUNTM_5,
    GRUNTM_6,
    GRUNTM_7,
    GRUNTM_8,
    GRUNTM_9,
    GRUNTM_10,
    GRUNTM_11,
    GRUNTM_12,  // unused
    GRUNTM_13,
    GRUNTM_14,
    GRUNTM_15,
    GRUNTM_16,
    GRUNTM_17,
    GRUNTM_18,
    GRUNTM_19,
    GRUNTM_20,
    GRUNTM_21,
    GRUNTM_22,  // unused
    GRUNTM_23,  // unused
    GRUNTM_24,
    GRUNTM_25,
    GRUNTM_26,  // unused
    GRUNTM_27,  // unused
    GRUNTM_28,
    GRUNTM_29,
    GRUNTM_30,  // unused
    GRUNTM_31,
};

#define GENTLEMAN 0x20
enum {
    PRESTON,
    EDWARD,
    GREGORY,
    VIRGIL,  // unused
    ALFRED,
};

#define SKIER 0x21
enum {
    ROXANNE,
    CLARISSA,
};

#define TEACHER 0x22
enum {
    COLETTE,
    HILLARY,
    SHIRLEY,
};

#define SABRINA 0x23
enum {
    SABRINA1,
};

#define BUG_CATCHER 0x24
enum {
    DON,
    ROB,
    ED,
    WADE1,
    BUG_CATCHER_BENNY,
    AL,
    JOSH,
    ARNIE1,
    KEN,
    WADE2,
    WADE3,
    DOUG,
    ARNIE2,
    ARNIE3,
    WADE4,
    WADE5,
    ARNIE4,
    ARNIE5,
    WAYNE,
};

#define FISHER 0x25
enum {
    JUSTIN,
    RALPH1,
    ARNOLD,
    KYLE,
    HENRY,
    MARVIN,
    TULLY1,
    ANDRE,
    RAYMOND,
    WILTON1,
    EDGAR,
    JONAH,
    MARTIN,
    STEPHEN,
    BARNEY,
    RALPH2,
    RALPH3,
    TULLY2,
    TULLY3,
    WILTON2,
    SCOTT,
    WILTON3,
    RALPH4,
    RALPH5,
    TULLY4,
};

#define SWIMMERM 0x26
enum {
    HAROLD,
    SIMON,
    RANDALL,
    CHARLIE,
    GEORGE,
    BERKE,
    KIRK,
    MATHEW,
    HAL,     // unused
    PATON,   // unused
    DARYL,   // unused
    WALTER,  // unused
    TONY,    // unused
    JEROME,
    TUCKER,
    RICK,  // unused
    CAMERON,
    SETH,
    JAMES,  // unused
    LEWIS,  // unused
    PARKER,
};

#define SWIMMERF 0x27
enum {
    ELAINE,
    PAULA,
    KAYLEE,
    SUSIE,
    DENISE,
    KARA,
    WENDY,
    LISA,   // unused
    JILL,   // unused
    MARY,   // unused
    KATIE,  // unused
    DAWN,
    TARA,  // unused
    NICOLE,
    LORI,
    JODY,  // unused
    NIKKI,
    DIANA,
    BRIANA,
};

#define SAILOR 0x28
enum {
    EUGENE,
    HUEY1,
    TERRELL,
    KENT,
    ERNEST,
    JEFF,
    GARRETT,
    KENNETH,
    STANLY,
    HARRY,
    HUEY2,
    HUEY3,
    HUEY4,
};

#define SUPER_NERD 0x29
enum {
    STAN,
    ERIC,
    GREGG,  // unused
    JAY,    // unused
    DAVE,   // unused
    SAM,
    TOM,
    PAT,
    SHAWN,
    TERU,
    RUSS,    // unused
    NORTON,  // unused
    HUGH,
    MARKUS,
};

#define RIVAL2 0x2a
enum {
    RIVAL2_1_CHIKORITA,
    RIVAL2_1_CYNDAQUIL,
    RIVAL2_1_TOTODILE,
    RIVAL2_2_CHIKORITA,
    RIVAL2_2_CYNDAQUIL,
    RIVAL2_2_TOTODILE,
};

#define GUITARIST 0x2b
enum {
    CLYDE,
    VINCENT,
};

#define HIKER 0x2c
enum {
    ANTHONY1,
    RUSSELL,
    PHILLIP,
    LEONARD,
    ANTHONY2,
    BENJAMIN,
    ERIK,
    MICHAEL,
    PARRY1,
    TIMOTHY,
    BAILEY,
    ANTHONY3,
    TIM,
    NOLAND,
    SIDNEY,
    KENNY,
    JIM,
    DANIEL,
    PARRY2,
    PARRY3,
    ANTHONY4,
    ANTHONY5,
};

#define BIKER 0x2d
enum {
    BIKER_BENNY,  // unused
    KAZU,         // unused
    DWAYNE,
    HARRIS,
    ZEKE,
    CHARLES,
    RILEY,
    JOEL,
    GLENN,
};

#define BLAINE 0x2e
enum {
    BLAINE1,
};

#define BURGLAR 0x2f
enum {
    DUNCAN,
    EDDIE,
    COREY,
};

#define FIREBREATHER 0x30
enum {
    OTIS,
    DICK,  // unused
    NED,   // unused
    BURT,
    BILL,
    WALT,
    RAY,
    LYLE,
};

#define JUGGLER 0x31
enum {
    IRWIN1,
    FRITZ,
    HORTON,
    IRWIN2,  // unused
    IRWIN3,  // unused
    IRWIN4,  // unused
};

#define BLACKBELT_T 0x32
enum {
    KENJI1,  // unused
    YOSHI,
    KENJI2,  // unused
    LAO,
    NOB,
    KIYO,
    LUNG,
    KENJI3,
    WAI,
};

#define EXECUTIVEM 0x33
enum {
    EXECUTIVEM_1,
    EXECUTIVEM_2,
    EXECUTIVEM_3,
    EXECUTIVEM_4,
};

#define PSYCHIC_T 0x34
enum {
    NATHAN,
    FRANKLIN,
    HERMAN,
    FIDEL,
    GREG,
    NORMAN,
    MARK,
    PHIL,
    RICHARD,
    GILBERT,
    JARED,
    RODNEY,
};

#define PICNICKER 0x35
enum {
    LIZ1,
    GINA1,
    BROOKE,
    KIM,
    CINDY,
    HOPE,
    SHARON,
    DEBRA,
    GINA2,
    ERIN1,
    LIZ2,
    LIZ3,
    HEIDI,
    EDNA,
    GINA3,
    TIFFANY1,
    TIFFANY2,
    ERIN2,
    TANYA,
    TIFFANY3,
    ERIN3,
    LIZ4,
    LIZ5,
    GINA4,
    GINA5,
    TIFFANY4,
};

#define CAMPER 0x36
enum {
    ROLAND,
    TODD1,
    IVAN,
    ELLIOT,
    BARRY,
    LLOYD,
    DEAN,
    SID,
    HARVEY,  // unused
    DALE,    // unused
    TED,
    TODD2,
    TODD3,
    THOMAS,  // unused
    LEROY,   // unused
    DAVID,   // unused
    JOHN,    // unused
    JERRY,
    SPENCER,
    TODD4,
    TODD5,
    QUENTIN,
};

#define EXECUTIVEF 0x37
enum {
    EXECUTIVEF_1,
    EXECUTIVEF_2,
};

#define SAGE 0x38
enum {
    CHOW,
    NICO,
    JIN,
    TROY,
    JEFFREY,
    PING,
    EDMOND,
    NEAL,
    LI,
    GAKU,
    MASA,
    KOJI,
};

#define MEDIUM 0x39
enum {
    MARTHA,
    GRACE,
    BETHANY,  // unused
    MARGRET,  // unused
    ETHEL,    // unused
    REBECCA,
    DORIS,
};

#define BOARDER 0x3a
enum {
    RONALD,
    BRAD,
    DOUGLAS,
};

#define POKEFANM 0x3b
enum {
    WILLIAM,
    DEREK1,
    ROBERT,
    JOSHUA,
    CARTER,
    TREVOR,
    BRANDON,
    JEREMY,
    COLIN,
    DEREK2,  // unused
    DEREK3,  // unused
    ALEX,
    REX,
    ALLAN,
};

#define KIMONO_GIRL 0x3c
enum {
    NAOKO_UNUSED,  // unused
    NAOKO,
    SAYO,
    ZUKI,
    KUNI,
    MIKI,
};

#define TWINS 0x3d
enum {
    AMYANDMAY1,
    ANNANDANNE1,
    ANNANDANNE2,
    AMYANDMAY2,
    JOANDZOE1,
    JOANDZOE2,
    MEGANDPEG1,
    MEGANDPEG2,
    LEAANDPIA1,
    LEAANDPIA2,  // unused
};

#define POKEFANF 0x3e
enum {
    BEVERLY1,
    RUTH,
    BEVERLY2,  // unused
    BEVERLY3,  // unused
    GEORGIA,
    JAIME,
};

#define RED 0x3f
enum {
    RED1,
};

#define BLUE 0x40
enum {
    BLUE1,
};

#define OFFICER 0x41
enum {
    KEITH,
    DIRK,
};

#define GRUNTF 0x42
enum {
    GRUNTF_1,
    GRUNTF_2,
    GRUNTF_3,
    GRUNTF_4,
    GRUNTF_5,
};

#define MYSTICALMAN 0x43
enum {
    EUSINE,
};

#define NUM_TRAINER_CLASSES MYSTICALMAN
