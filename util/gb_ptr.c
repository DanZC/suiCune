#include "../constants.h"
#include "gb_ptr.h"

bool IsROMAddr(uint32_t addr) {
    return ((addr & 0xffff) < 0x8000);
}

struct priv_t {
    /* Pointer to allocated memory holding GB file. */
    uint8_t *rom;
    /* Pointer to allocated memory holding save file. */
    uint8_t *cart_ram;
};

// Converts a GB rom address to a real address.
static void* GBROMToRAMAddr(uint16_t hl) {
    if(hl < ROM_N_ADDR) {
        return ((struct priv_t*)gb.direct.priv)->rom + (hl - ROM_0_ADDR);
    }
    else {
        return ((struct priv_t*)gb.direct.priv)->rom + (ROM_BANK_SIZE * (gb.selected_rom_bank)) + (hl - ROM_N_ADDR);
    }
}

// Converts a GB address to a real address.
void* GBToRAMAddr(uint16_t hl) {
    if(hl < 0x8000)
        return GBROMToRAMAddr(hl);
    if(hl >= WRAM0_Begin && hl < WRAM0_End) {
        return wram->wram0 + (hl - WRAM0_Begin);
    }
    if(hl >= WRAM1_Begin && hl < WRAM1_End) {
        return wram->wram0 + (0x1000 * (gb.cgb.wramBank - 1)) + (hl - WRAM0_Begin);
    }
    if(hl >= HRAM_Begin && hl < HRAM_End) {
        return (gb.hram + 0x80) + (hl - HRAM_Begin);
    }
    if(hl >= VRAM_Begin && hl < VRAM_End) {
        return gb.vram + (VRAM_BANK_SIZE * gb.cgb.vramBank) + (hl - VRAM_Begin);
    }
    if(hl >= SRAM_Begin && hl < SRAM_End) {
        return ((struct priv_t*)gb.direct.priv)->cart_ram + (0x2000 * gb.cart_ram_bank) + (hl - SRAM_Begin);
    }
    return NULL;
}

// Converts a GB rom address to a real address.
void* AbsGBROMToRAMAddr(uint32_t hl) {
    struct BankAddr ba = AbsROMAddrToBankAddr(hl);
    if(ba.bank == 0)
        return ((struct priv_t*)gb.direct.priv)->rom + (ba.addr & 0x3fff);
    return ((struct priv_t*)gb.direct.priv)->rom + (ROM_BANK_SIZE * (ba.bank)) + (ba.addr & 0x3fff);
}

// Converts a GB rom bank and address to a real address.
void* AbsGBROMBankAddrToRAMAddr(uint8_t bank, uint16_t addr) {
    if(bank == 0)
        return ((struct priv_t*)gb.direct.priv)->rom + (addr & 0x3fff);
    return ((struct priv_t*)gb.direct.priv)->rom + (ROM_BANK_SIZE * (bank)) + (addr & 0x3fff);
}

// Converts a GB bank and address to a real address.
void* AbsGBBankAddrToRAMAddr(uint8_t bank, uint16_t addr) {
    if(addr < 0x8000)
        return AbsGBROMBankAddrToRAMAddr(bank, addr);
    if(addr >= WRAM0_Begin && addr < WRAM0_End) {
        return wram->wram0 + (addr - WRAM0_Begin);
    }
    if(addr >= WRAM1_Begin && addr < WRAM1_End) {
        return wram->wram0 + (0x1000 * bank) + (addr - WRAM0_Begin);
    }
    if(addr >= HRAM_Begin && addr < HRAM_End) {
        return (uint8_t*)&hram + (addr - HRAM_Begin);
    }
    if(addr >= VRAM_Begin && addr < VRAM_End) {
        return (uint8_t*)vram + (VRAM_BANK_SIZE * bank) + (addr - VRAM_Begin);
    }
    if(addr >= SRAM_Begin && addr < SRAM_End) {
        return ((struct priv_t*)gb.direct.priv)->cart_ram + (0x2000 * bank) + (addr - SRAM_Begin);
    }
    return NULL;
}

// Converts a GB absolute ram address to real address.
void* AbsGBToRAMAddr(uint32_t hl) {
    if(hl == 0)
        return NULL;
    if(IsROMAddr(hl))
        return AbsGBROMToRAMAddr(hl);
    struct BankAddr ba = AbsRAMAddrToBankAddr(hl);
    if(ba.addr >= WRAM0_Begin && ba.addr < WRAM0_End) {
        return wram->wram0 + (ba.addr - WRAM0_Begin);
    }
    if(ba.addr >= WRAM1_Begin && ba.addr < WRAM1_End) {
        return wram->wram0 + (0x1000 * ba.bank) + (ba.addr - WRAM1_Begin);
    }
    if(ba.addr >= HRAM_Begin && ba.addr < HRAM_End) {
        return (uint8_t*)&hram + (ba.addr - HRAM_Begin);
    }
    if(ba.addr >= VRAM_Begin && ba.addr < VRAM_End) {
        return (uint8_t*)vram + (VRAM_BANK_SIZE * ba.bank) + (ba.addr - VRAM_Begin);
    }
    if(ba.addr >= SRAM_Begin && ba.addr < SRAM_End) {
        return ((struct priv_t*)gb.direct.priv)->cart_ram + (0x2000 * ba.bank) + (ba.addr - SRAM_Begin);
    }
    return NULL;
}

// Converts a real address to a GB address.
uint16_t RAMAddrToGB(void* addr) {
    uint8_t* p = addr;
    if((p - wram->wram0) >= 0 && (p - wram->wram0) < 0x1000)
        return WRAM0_Begin + (p - wram->wram0);
    if((p - wram->wram1) >= 0 && (p - wram->wram1) < 0x6000)
        return WRAM1_Begin + ((p - wram->wram1) % 0x1000);
    if((p - (uint8_t*)&hram) >= 0 && (p - (uint8_t*)&hram) < (long long)sizeof(hram))
        return HRAM_Begin + (p - (uint8_t*)&hram);
    if((p - (uint8_t*)vram) >= 0 && (p - (uint8_t*)vram) < (long long)sizeof(*vram))
        return VRAM_Begin + (p - (uint8_t*)vram);
    if((p - ((struct priv_t*)gb.direct.priv)->rom) >= 0 && (p - ((struct priv_t*)gb.direct.priv)->rom) < ROM_BANK_SIZE)
        return ROM_0_ADDR + (p - ((struct priv_t*)gb.direct.priv)->rom);
    if((p - ((struct priv_t*)gb.direct.priv)->rom) >= ROM_BANK_SIZE && (p - ((struct priv_t*)gb.direct.priv)->rom) < ROM_BANK_SIZE * 128)
        return ROM_N_ADDR + ((p - ((struct priv_t*)gb.direct.priv)->rom) & 0x3fff);
    if((p - ((struct priv_t*)gb.direct.priv)->cart_ram) >= 0 && (p - ((struct priv_t*)gb.direct.priv)->cart_ram) < SRAM_SIZE)
        return SRAM_Begin + (p - ((struct priv_t*)gb.direct.priv)->cart_ram);
    return 0;
}

// Converts a real address to a GB absolute ram address.
uint32_t RAMAddrToAbsGB(void* addr) {
    uint8_t* p = addr;
    if((wram->wram0 - p) >= 0 && (wram->wram0 - p) < 0x1000)
        return WRAM0_Begin + (wram->wram0 - p);
    if((wram->wram1 - p) >= 0 && (wram->wram1 - p) < 0x6000)
        return (WRAM1_Begin + (wram->wram1 - p)) | (((wram->wram0 - p) / 0x1000) << 16);
    if(((uint8_t*)&hram - p) >= 0 && ((uint8_t*)&hram - p) < (long long)sizeof(hram))
        return HRAM_Begin + ((uint8_t*)&hram - p);
    if(((uint8_t*)vram - p) >= 0 && ((uint8_t*)vram - p) < (long long)sizeof(*vram))
        return (VRAM_Begin + ((uint8_t*)vram - p)) | ((((uint8_t*)vram - p) / VRAM_BANK_SIZE) << 16);
    return 0;
}

struct BankAddr AbsRAMAddrToBankAddr(uint32_t addr) {
    return (struct BankAddr) {.bank = (uint8_t)MBANK(addr), .addr = (uint16_t)(addr & 0xffff)};
}

struct BankAddr AbsROMAddrToBankAddr(uint32_t addr) {
    return (struct BankAddr) {.bank = (uint8_t)BANK(addr), .addr = (uint16_t)(addr & 0x3fff)};
}

uint32_t BankAddrToAbsRAMAddr(uint8_t bank, uint16_t addr) {
    return (uint32_t)(addr | (bank << 16));
}

uint8_t* SRAMPtr(uint32_t addr) {
    return ((struct priv_t*)gb.direct.priv)->cart_ram + (0x2000 * MBANK(addr)) + ((addr & 0xffff) - SRAM_Begin);
}

static void SafeCallGBInternal(uint32_t address) {
    uint8_t bank = hram.hROMBank;
    gb_write(MBC3RomBank, BANK(address));
    hram.hROMBank = BANK(address);
    CALL(address);
    gb_write(MBC3RomBank, bank);
    hram.hROMBank = bank;
}

void SafeCallGB(uint32_t address, struct cpu_registers_s* regs) {
    if(regs != &gb.cpu_reg)
    {
        struct cpu_registers_s copy = gb.cpu_reg;
        gb.cpu_reg = *regs;
        SafeCallGBInternal(address);
        *regs = gb.cpu_reg;
        gb.cpu_reg = copy;
    }
    else 
    {
        struct cpu_registers_s copy = gb.cpu_reg;
        SafeCallGBInternal(address);
        gb.cpu_reg = copy;
    }
}

void SafeCallGBAuto(uint32_t address) {
    return SafeCallGB(address, &gb.cpu_reg);
}

struct cpu_registers_s SafeCallGBAutoRet(uint32_t address) {
    struct cpu_registers_s copy = gb.cpu_reg;
    SafeCallGBInternal(address);
    struct cpu_registers_s ret = gb.cpu_reg;
    gb.cpu_reg = copy;
    return ret;
}