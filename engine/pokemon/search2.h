uint8_t v_FindPartyMonAboveLevel(uint8_t level);
uint8_t v_FindPartyMonAtLeastThatHappy(uint8_t happiness);
u8_flag_s v_FindPartyMonThatSpecies(species_t b);
bool v_FindPartyMonThatSpeciesYourTrainerID(species_t b);
uint8_t FindAtLeastThatHappy(struct PartyMon* bc, uint8_t happiness);
uint8_t FindAboveLevel(struct PartyMon* bc, uint8_t level);
u8_flag_s FindThatSpecies(species_t b);
uint8_t RetroactivelyIgnoreEggs(uint8_t);
