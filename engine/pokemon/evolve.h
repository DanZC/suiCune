void EvolvePokemon(void);
void EvolveAfterBattle(void);
void EvolveAfterBattle_MasterLoop(void);
void UpdateSpeciesNameIfNotNicknamed(void);
void CancelEvolution(void);
void IsMonHoldingEverstone(void);
void CongratulationsYourPokemonText(void);
void EvolvedIntoText(void);
void StoppedEvolvingText(void);
void EvolvingText(void);
void LearnLevelMoves(void);
void FillMoves(void);
void FillMoves_Conv(move_t* de, uint8_t* pp, species_t species, uint8_t level);
void ShiftMoves(void);
void ShiftMoves_Conv(move_t* hl);
void EvoFlagAction(void);
void GetPreEvolution(void);