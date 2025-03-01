#include <stdint.h>
#include "prefecture_to_postcode_pairs.h"
#if defined(_CRYSTAL_AU) // AU build.
const uint8_t PrefectureZipcodeFormat[] = {
    0, // AU-NSW
    0, // AU-QLD
    0, // AU-SA
    0, // AU-TAS
    0, // AU-VIC
    0, // AU-WA
    0, // AU-ACT
    0, // AU-NT
    0, // NZ-AUK
    0, // NZ-BOP
    0, // NZ-CAN
    0, // NZ-CIT
    0, // NZ-GIS
    0, // NZ-WGN
    0, // NZ-HKB
    0, // NZ-MWT
    0, // NZ-MBH
    0, // NZ-NSN
    0, // NZ-NTL
    0, // NZ-OTA
    0, // NZ-STL
    0, // NZ-TKI
    0, // NZ-TAS
    0, // NZ-WKO
    0, // NZ-WTC
};

const uint8_t ZipcodeFormatLengths[] = {
    4, //  0:   0-9   0-9   0-9   0-9
};






#elif defined(_CRYSTAL_EU) // EU build.
const uint8_t PrefectureZipcodeFormat[] = {
    0,  // EU-AD
    2,  // EU-AL
    2,  // EU-AT
    3,  // EU-BA
    2,  // EU-BE
    2,  // EU-BG
    4,  // EU-BY
    2,  // EU-CH
    3,  // EU-CZ
    3,  // EU-DE
    2,  // EU-DK
    3,  // EU-EE
    3,  // EU-ES
    3,  // EU-FI
    3,  // EU-FR
    8,  // EU-GB
    3,  // EU-GR
    3,  // EU-HR
    2,  // EU-HU
    7,  // EU-IE
    1,  // EU-IS
    3,  // EU-IT
    2,  // EU-LI
    2,  // EU-LT
    2,  // EU-LU
    10, // EU-LV
    11, // EU-MD
    9,  // EU-MT
    6,  // EU-NL
    2,  // EU-NO
    14, // EU-PL
    5,  // EU-PT
    4,  // EU-RO
    3,  // EU-RS
    4,  // EU-RU
    15, // EU-SE
    12, // EU-SI
    3,  // EU-SK
    13, // EU-SM
    3,  // EU-UA
};

const uint8_t ZipcodeFormatLengths[] = {
    3, //  0:   -     -     -
    3, //  1:   0-9   0-9   0-9
    4, //  2:   0-9   0-9   0-9   0-9
    5, //  3:   0-9   0-9   0-9   0-9   0-9
    6, //  4:   0-9   0-9   0-9   0-9   0-9   0-9
    8, //  5:   0-9   0-9   0-9   0-9   0-9   0-9   0-9
    6, //  6:   0-9   0-9   0-9   0-9   A-Z   A-Z
    8, //  7:   A-Z   0-9         0-Z   0-Z   0-Z   0-Z   0-Z
    8, //  8:   A-Z   0-Z   0-Z   0-Z   0-Z   Blank+A-Z   Blank+A-Z
    6, //  9:   A-Z   A-Z   A-Z         0-9   0-9
    7, // 10:   L     V     0-9   0-9   0-9   0-9
    7, // 11:   M     D     0-9   0-9   0-9   0-9
    7, // 12:   S     I     0-9   0-9   0-9   0-9
    5, // 13:   4     7      8     9    0-9
    6, // 14:   0-9   0-9    -    0-9   0-9   0-9
    6, // 15:   0-9   0-9   0-9         0-9   0-9
};






#else // US build.
const uint8_t PrefectureZipcodeFormat[] = {
    0, // US-AL
    0, // US-AK
    0, // US-AZ
    0, // US-AR
    0, // US-CA
    0, // US-CO
    0, // US-CT
    0, // US-DE
    0, // US-FL
    0, // US-GA
    0, // US-HI
    0, // US-ID
    0, // US-IL
    0, // US-IN
    0, // US-IA
    0, // US-KS
    0, // US-KY
    0, // US-LA
    0, // US-ME
    0, // US-MD
    0, // US-MA
    0, // US-MI
    0, // US-MN
    0, // US-MS
    0, // US-MO
    0, // US-MT
    0, // US-NE
    0, // US-NV
    0, // US-NH
    0, // US-NJ
    0, // US-NM
    0, // US-NY
    0, // US-NC
    0, // US-ND
    0, // US-OH
    0, // US-OK
    0, // US-OR
    0, // US-PA
    0, // US-RI
    0, // US-SC
    0, // US-SD
    0, // US-TN
    0, // US-TX
    0, // US-UT
    0, // US-VT
    0, // US-VA
    0, // US-WA
    0, // US-WV
    0, // US-WI
    0, // US-WY
    1, // CA-AB
    1, // CA-BC
    1, // CA-MB
    1, // CA-NB
    1, // CA-NL
    1, // CA-NS
    1, // CA-ON
    1, // CA-PE
    1, // CA-QC
    1, // CA-SK
    1, // CA-NT
    1, // CA-NU
    1, // CA-YT
};

const uint8_t ZipcodeFormatLengths[] = {
    5, //  0:   0-9   0-9   0-9   0-9   0-9
    7, //  1:   A-Z   0-9   A-Z         0-9   A-Z   0-9
};
#endif
