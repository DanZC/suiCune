// void NamesPointers(void);
extern const char (*const NamesPointers[])[20];
uint8_t* GetName(uint8_t type, uint16_t index);
void GetName_GB(void);
void GetNthString(void);
uint16_t GetNthString_GB(uint16_t hl, uint8_t a);
uint8_t* GetBasePokemonName(species_t a);
uint8_t* GetPokemonName(species_t index);
void GetPokemonName_GB(void);
uint8_t* GetItemName(item_t a);
uint8_t* GetTMHMName(item_t a);
uint8_t* GetMoveName(move_t move);
#include "hm_moves.h"
