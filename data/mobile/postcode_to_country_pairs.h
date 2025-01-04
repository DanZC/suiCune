#pragma once

// Combine these groups together somehow
#if defined(_CRYSTAL_AU)
enum {
    COUNTRY_AU,
    COUNTRY_NZ,
};
#elif defined(_CRYSTAL_EU)
enum {
    COUNTRY_AD,
    COUNTRY_AL,
    COUNTRY_AT,
    COUNTRY_BA,
    COUNTRY_BE,
    COUNTRY_BG,
    COUNTRY_BY,
    COUNTRY_CH,
    COUNTRY_CZ,
    COUNTRY_DE,
    COUNTRY_DK,
    COUNTRY_EE,
    COUNTRY_ES,
    COUNTRY_FI,
    COUNTRY_FR,
    COUNTRY_GB,
    COUNTRY_GR,
    COUNTRY_HR,
    COUNTRY_HU,
    COUNTRY_IE,
    COUNTRY_IS,
    COUNTRY_IT,
    COUNTRY_LI,
    COUNTRY_LT,
    COUNTRY_LU,
    COUNTRY_LV,
    COUNTRY_MD,
    COUNTRY_MT,
    COUNTRY_NL,
    COUNTRY_NO,
    COUNTRY_PL,
    COUNTRY_PT,
    COUNTRY_RO,
    COUNTRY_RS,
    COUNTRY_RU,
    COUNTRY_SE,
    COUNTRY_SI,
    COUNTRY_SK,
    COUNTRY_SM,
    COUNTRY_UA,
};
#else // US Build
enum {
    COUNTRY_US,
    COUNTRY_CA,
};
#endif

extern const uint16_t PrefectureToCountry[];
