#pragma once

bool IsROMAddr(uint32_t addr);
void* GBToRAMAddr(uint16_t hl);
void* AbsGBROMToRAMAddr(uint32_t hl);
void* AbsGBROMBankAddrToRAMAddr(uint8_t bank, uint16_t addr);
void* AbsGBBankAddrToRAMAddr(uint8_t bank, uint16_t addr);
void* AbsGBToRAMAddr(uint32_t hl);
uint16_t RAMAddrToGB(void* addr);
uint32_t RAMAddrToAbsGB(void* addr);
struct BankAddr AbsRAMAddrToBankAddr(uint32_t addr);
struct BankAddr AbsROMAddrToBankAddr(uint32_t addr);
uint32_t BankAddrToAbsRAMAddr(uint8_t bank, uint16_t addr);
uint8_t* SRAMPtr(uint32_t addr);
void SafeCallGB(uint32_t address, struct cpu_registers_s* regs);
void SafeCallGBAuto(uint32_t address);
struct cpu_registers_s SafeCallGBAutoRet(uint32_t address);
