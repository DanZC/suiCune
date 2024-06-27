void BeastsCheck(void);
void MonCheck(void);
bool CheckOwnMonAnywhere(species_t species);
bool CheckOwnMon(const struct BoxMon* hl, const uint8_t* ot, species_t species);
extern const uint32_t SearchBoxAddressTable[];
void UpdateOTPointer(void);
