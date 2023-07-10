#pragma once

bool IsROMAddr(uint32_t addr);
void* GBToRAMAddr(uint16_t hl);
void* AbsGBToRAMAddr(uint32_t hl);
uint16_t RAMAddrToGB(void* addr);
uint32_t RAMAddrToAbsGB(void* addr);
struct BankAddr AbsRAMAddrToBankAddr(uint32_t addr);
struct BankAddr AbsROMAddrToBankAddr(uint32_t addr);
uint32_t BankAddrToAbsRAMAddr(uint8_t bank, uint16_t addr);