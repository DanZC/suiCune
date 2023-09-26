// void NamesPointers(void);
extern const char (*const NamesPointers[20])[];
void GetName(void);
void GetName_Conv(void);
uint8_t* GetName_Conv2(uint8_t type, uint8_t index);
void GetNthString(void);
uint16_t GetNthString_Conv(uint16_t hl, uint8_t a);
void GetBasePokemonName(void);
void GetPokemonName(void);
void GetPokemonName_Conv(void);
uint8_t* GetPokemonName_Conv2(uint8_t index);
void GetItemName(void);
uint8_t* GetItemName_Conv2(void);
void GetTMHMName(void);
void GetTMHMName_Conv(void);
void GetMoveName(void);
#include "hm_moves.h"
