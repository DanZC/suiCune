#include <stdint.h>
#include "postcode_to_country_pairs.h"
#if defined(_CRYSTAL_AU) // AU build.
const uint16_t PrefectureToCountry[] = {
    COUNTRY_AU, // AU-NSW
    COUNTRY_AU, // AU-QLD
    COUNTRY_AU, // AU-SA
    COUNTRY_AU, // AU-TAS
    COUNTRY_AU, // AU-VIC
    COUNTRY_AU, // AU-WA
    COUNTRY_AU, // AU-ACT
    COUNTRY_AU, // AU-NT
    COUNTRY_NZ, // NZ-AUK
    COUNTRY_NZ, // NZ-BOP
    COUNTRY_NZ, // NZ-CAN
    COUNTRY_NZ, // NZ-CIT
    COUNTRY_NZ, // NZ-GIS
    COUNTRY_NZ, // NZ-WGN
    COUNTRY_NZ, // NZ-HKB
    COUNTRY_NZ, // NZ-MWT
    COUNTRY_NZ, // NZ-MBH
    COUNTRY_NZ, // NZ-NSN
    COUNTRY_NZ, // NZ-NTL
    COUNTRY_NZ, // NZ-OTA
    COUNTRY_NZ, // NZ-STL
    COUNTRY_NZ, // NZ-TKI
    COUNTRY_NZ, // NZ-TAS
    COUNTRY_NZ, // NZ-WKO
    COUNTRY_NZ, // NZ-WTC
};






#elif defined(_CRYSTAL_EU) // EU build.
const uint16_t PrefectureToCountry[] = {
     0, // EU-AD
     1, // EU-AL
     2, // EU-AT
     3, // EU-BA
     4, // EU-BE
     5, // EU-BG
     6, // EU-BY
     7, // EU-CH
     8, // EU-CZ
     9, // EU-DE
    10, // EU-DK
    11, // EU-EE
    12, // EU-ES
    13, // EU-FI
    14, // EU-FR
    15, // EU-GB
    16, // EU-GR
    17, // EU-HR
    18, // EU-HU
    19, // EU-IE
    20, // EU-IS
    21, // EU-IT
    22, // EU-LI
    23, // EU-LT
    24, // EU-LU
    25, // EU-LV
    26, // EU-MD
    27, // EU-MT
    28, // EU-NL
    29, // EU-NO
    30, // EU-PL
    31, // EU-PT
    32, // EU-RO
    33, // EU-RS
    34, // EU-RU
    35, // EU-SE
    36, // EU-SI
    37, // EU-SK
    38, // EU-SM
    39, // EU-UA
};






#else // US build.
const uint16_t PrefectureToCountry[] = {
	COUNTRY_US, // US-AL
	COUNTRY_US, // US-AK
	COUNTRY_US, // US-AZ
	COUNTRY_US, // US-AR
	COUNTRY_US, // US-CA
	COUNTRY_US, // US-CO
	COUNTRY_US, // US-CT
	COUNTRY_US, // US-DE
	COUNTRY_US, // US-FL
	COUNTRY_US, // US-GA
	COUNTRY_US, // US-HI
	COUNTRY_US, // US-ID
	COUNTRY_US, // US-IL
	COUNTRY_US, // US-IN
	COUNTRY_US, // US-IA
	COUNTRY_US, // US-KS
	COUNTRY_US, // US-KY
	COUNTRY_US, // US-LA
	COUNTRY_US, // US-ME
	COUNTRY_US, // US-MD
	COUNTRY_US, // US-MA
	COUNTRY_US, // US-MI
	COUNTRY_US, // US-MN
	COUNTRY_US, // US-MS
	COUNTRY_US, // US-MO
	COUNTRY_US, // US-MT
	COUNTRY_US, // US-NE
	COUNTRY_US, // US-NV
	COUNTRY_US, // US-NH
	COUNTRY_US, // US-NJ
	COUNTRY_US, // US-NM
	COUNTRY_US, // US-NY
	COUNTRY_US, // US-NC
	COUNTRY_US, // US-ND
	COUNTRY_US, // US-OH
	COUNTRY_US, // US-OK
	COUNTRY_US, // US-OR
	COUNTRY_US, // US-PA
	COUNTRY_US, // US-RI
	COUNTRY_US, // US-SC
	COUNTRY_US, // US-SD
	COUNTRY_US, // US-TN
	COUNTRY_US, // US-TX
	COUNTRY_US, // US-UT
	COUNTRY_US, // US-VT
	COUNTRY_US, // US-VA
	COUNTRY_US, // US-WA
	COUNTRY_US, // US-WV
	COUNTRY_US, // US-WI
	COUNTRY_US, // US-WY
	COUNTRY_CA, // CA-AB
	COUNTRY_CA, // CA-BC
	COUNTRY_CA, // CA-MB
	COUNTRY_CA, // CA-NB
	COUNTRY_CA, // CA-NL
	COUNTRY_CA, // CA-NS
	COUNTRY_CA, // CA-ON
	COUNTRY_CA, // CA-PE
	COUNTRY_CA, // CA-QC
	COUNTRY_CA, // CA-SK
	COUNTRY_CA, // CA-NT
	COUNTRY_CA, // CA-NU
	COUNTRY_CA, // CA-YT
};
#endif