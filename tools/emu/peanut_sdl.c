/**
 * MIT License
 * Copyright (c) 2018 Mahyar Koshkouei
 *
 * An example of using the peanut_gb.h library. This example application uses
 * SDL2 to draw the screen and get input.
 */

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL.h>

#include "minigb_apu/minigb_apu.h"
#include "peanut_gb.h"
#include "../../home/lcd.h"
#include "rom_patches.h"

struct gb_s gb;
#define ROM_SIZE 0x200000
void (*redirectFunc[ROM_SIZE])(void);
void (*convertedFunc[ROM_SIZE])(void);

struct priv_t {
    /* Pointer to allocated memory holding GB file. */
    uint8_t *rom;
    /* Pointer to allocated memory holding save file. */
    uint8_t *cart_ram;

    /* Colour palette for each BG, OBJ0, and OBJ1. */
    uint16_t selected_palette[3][4];
    uint16_t fb[LCD_HEIGHT][LCD_WIDTH];
};

struct priv_t priv =
    {
        .rom = NULL,
        .cart_ram = NULL};

/* Must be freed */
SDL_Renderer *renderer;
SDL_Texture *texture;
SDL_Window *window;
SDL_GameController *controller = NULL;

char *rom_file_name = "baserom.gbc";
char *save_file_name = NULL;

/**
 * Tick the internal RTC by one second.
 * This was taken from SameBoy, which is released under MIT Licence.
 */
void gb_tick_rtc(void) {
    /* is timer running? */
    if ((gb.cart_rtc[4] & 0x40) == 0) {
        if (++gb.rtc_bits.sec == 60) {
            gb.rtc_bits.sec = 0;

            if (++gb.rtc_bits.min == 60) {
                gb.rtc_bits.min = 0;

                if (++gb.rtc_bits.hour == 24) {
                    gb.rtc_bits.hour = 0;

                    if (++gb.rtc_bits.yday == 0) {
                        if (gb.rtc_bits.high & 1) /* Bit 8 of days*/
                        {
                            gb.rtc_bits.high |= 0x80; /* Overflow bit */
                        }

                        gb.rtc_bits.high ^= 1;
                    }
                }
            }
        }
    }
}

/**
 * Set initial values in RTC.
 * Should be called after gb_init().
 */
void gb_set_rtc(const struct tm *const time) {
    gb.cart_rtc[0] = time->tm_sec;
    gb.cart_rtc[1] = time->tm_min;
    gb.cart_rtc[2] = time->tm_hour;
    gb.cart_rtc[3] = time->tm_yday & 0xFF; /* Low 8 bits of day counter. */
    gb.cart_rtc[4] = time->tm_yday >> 8;   /* High 1 bit of day counter. */
}

/**
 * Internal function used to read bytes.
 */
uint8_t gb_read(const uint_fast16_t addr) {
    switch (addr >> 12) {
        case 0x0:

        /* TODO: BIOS support. */
        case 0x1:
        case 0x2:
        case 0x3:
            return gb.gb_rom_read(addr);

        case 0x4:
        case 0x5:
        case 0x6:
        case 0x7:
            if (gb.mbc == 1 && gb.cart_mode_select)
                return gb.gb_rom_read(
                    addr + ((gb.selected_rom_bank & 0x1F) - 1) * ROM_BANK_SIZE);
            else
                return gb.gb_rom_read(addr + (gb.selected_rom_bank - 1) * ROM_BANK_SIZE);

        case 0x8:
        case 0x9:
            return gb.vram[addr - gb.cgb.vramBankOffset];

        case 0xA:
        case 0xB:
            if (gb.cart_ram && gb.enable_cart_ram) {
                if (gb.mbc == 3 && gb.cart_ram_bank >= 0x08)
                    return gb.cart_rtc[gb.cart_ram_bank - 0x08];
                else
                    return gb.gb_cart_ram_read(addr - gb.cart_ram_bank_offset);
            }

            return 0xFF;

        case 0xC:
            return gb.wram[addr - WRAM_0_ADDR];

        case 0xD:
            return gb.wram[addr - gb.cgb.wramBankOffset];

        case 0xE:
            return gb.wram[addr - ECHO_ADDR];

        case 0xF:
            if (addr < OAM_ADDR)
                return gb.wram[(addr - 0x2000) - gb.cgb.wramBankOffset];

            if (addr < UNUSED_ADDR)
                return gb.oam[addr - OAM_ADDR];

            /* Unusable memory area. Reading from this area returns 0.*/
            if (addr < IO_ADDR)
                return 0xFF;

            /* HRAM */
            if (HRAM_ADDR <= addr && addr < INTR_EN_ADDR)
                return gb.hram[addr - IO_ADDR];

            if ((addr >= 0xFF10) && (addr <= 0xFF3F)) {
                return audio_read(addr);
            }

            /* IO and Interrupts. */
            switch (addr & 0xFF) {
                /* IO Registers */
                case 0x00:
                    return 0xC0 | gb.gb_reg.P1;

                case 0x01:
                    return gb.gb_reg.SB;

                case 0x02:
                    return gb.gb_reg.SC;

                /* Timer Registers */
                case 0x04:
                    return gb.gb_reg.DIV;

                case 0x05:
                    return gb.gb_reg.TIMA;

                case 0x06:
                    return gb.gb_reg.TMA;

                case 0x07:
                    return gb.gb_reg.TAC;

                /* Interrupt Flag Register */
                case 0x0F:
                    return gb.gb_reg.IF;

                /* LCD Registers */
                case 0x40:
                    return gb.gb_reg.LCDC;

                case 0x41:
                    return (gb.gb_reg.STAT & STAT_USER_BITS) |
                           (gb.gb_reg.LCDC & LCDC_ENABLE ? gb.lcd_mode : LCD_VBLANK);

                case 0x42:
                    return gb.gb_reg.SCY;

                case 0x43:
                    return gb.gb_reg.SCX;

                case 0x44:
                    return gb.gb_reg.LY;

                case 0x45:
                    return gb.gb_reg.LYC;

                /* DMA Register */
                case 0x46:
                    return gb.gb_reg.DMA;

                /* DMG Palette Registers */
                case 0x47:
                    return gb.gb_reg.BGP;

                case 0x48:
                    return gb.gb_reg.OBP0;

                case 0x49:
                    return gb.gb_reg.OBP1;

                /* Window Position Registers */
                case 0x4A:
                    return gb.gb_reg.WY;

                case 0x4B:
                    return gb.gb_reg.WX;

                /* Speed Switch*/
                case 0x4D:
                    return (gb.cgb.doubleSpeed << 7) + gb.cgb.doubleSpeedPrep;

                /* CGB VRAM Bank*/
                case 0x4F:
                    return gb.cgb.vramBank | 0xFE;

                /* CGB DMA*/
                case 0x51:
                    return (gb.cgb.dmaSource >> 8);
                case 0x52:
                    return (gb.cgb.dmaSource & 0xF0);
                case 0x53:
                    return (gb.cgb.dmaDest >> 8);
                case 0x54:
                    return (gb.cgb.dmaDest & 0xF0);
                case 0x55:
                    return (gb.cgb.dmaActive << 7) | (gb.cgb.dmaSize - 1);

                /* IR Register*/
                case 0x56:
                    return gb.hram[0x56];

                /* CGB BG Palette Index*/
                case 0x68:
                    return (gb.cgb.BGPaletteID & 0x3F) + (gb.cgb.BGPaletteInc << 7);

                /* CGB BG Palette*/
                case 0x69:
                    return gb.cgb.BGPalette[(gb.cgb.BGPaletteID & 0x3F)];

                /* CGB OAM Palette Index*/
                case 0x6A:
                    return (gb.cgb.OAMPaletteID & 0x3F) + (gb.cgb.OAMPaletteInc << 7);

                /* CGB OAM Palette*/
                case 0x6B:
                    return gb.cgb.OAMPalette[(gb.cgb.OAMPaletteID & 0x3F)];

                /* CGB WRAM Bank*/
                case 0x70:
                    return gb.cgb.wramBank;

                /* Interrupt Enable Register */
                case 0xFF:
                    return gb.gb_reg.IE;

                /* Unused registers return 1 */
                default:
                    return 0xFF;
            }
    }

    (gb.gb_error)(GB_INVALID_READ, addr);
    return 0xFF;
}

/**
 * Internal function used to write bytes.
 */
void gb_write(const uint_fast16_t addr, const uint8_t val) {
    switch (addr >> 12) {
        case 0x0:
        case 0x1:
            if (gb.mbc == 2 && addr & 0x10)
                return;
            else if (gb.mbc > 0 && gb.cart_ram)
                gb.enable_cart_ram = ((val & 0x0F) == 0x0A);

            return;

        case 0x2:
            if (gb.mbc == 5) {
                gb.selected_rom_bank = (gb.selected_rom_bank & 0x100) | val;
                gb.selected_rom_bank =
                    gb.selected_rom_bank & gb.num_rom_banks_mask;
                return;
            }

            /* Intentional fall through. */

        case 0x3:
            if (gb.mbc == 1) {
                // selected_rom_bank = val & 0x7;
                gb.selected_rom_bank = (val & 0x1F) | (gb.selected_rom_bank & 0x60);

                if ((gb.selected_rom_bank & 0x1F) == 0x00)
                    gb.selected_rom_bank++;
            } else if (gb.mbc == 2 && addr & 0x10) {
                gb.selected_rom_bank = val & 0x0F;

                if (!gb.selected_rom_bank)
                    gb.selected_rom_bank++;
            } else if (gb.mbc == 3) {
                gb.selected_rom_bank = val & 0x7F;

                if (!gb.selected_rom_bank)
                    gb.selected_rom_bank++;
            } else if (gb.mbc == 5)
                gb.selected_rom_bank = (val & 0x01) << 8 | (gb.selected_rom_bank & 0xFF);

            gb.selected_rom_bank = gb.selected_rom_bank & gb.num_rom_banks_mask;
            return;

        case 0x4:
        case 0x5:
            if (gb.mbc == 1) {
                gb.cart_ram_bank = (val & 3);
                gb.cart_ram_bank_offset = 0xA000 - (gb.cart_ram_bank << 13);
                gb.selected_rom_bank = ((val & 3) << 5) | (gb.selected_rom_bank & 0x1F);
                gb.selected_rom_bank = gb.selected_rom_bank & gb.num_rom_banks_mask;
            } else if (gb.mbc == 3) {
                gb.cart_ram_bank = val;
                gb.cart_ram_bank_offset = 0xA000 - ((gb.cart_ram_bank & 3) << 13);
            } else if (gb.mbc == 5) {
                gb.cart_ram_bank = (val & 0x0F);
                gb.cart_ram_bank_offset = 0xA000 - (gb.cart_ram_bank << 13);
            }
            return;

        case 0x6:
        case 0x7:
            gb.cart_mode_select = (val & 1);
            return;

        case 0x8:
        case 0x9:
            gb.vram[addr - gb.cgb.vramBankOffset] = val;
            return;

        case 0xA:
        case 0xB:
            if (gb.cart_ram && gb.enable_cart_ram) {
                if (gb.mbc == 3 && gb.cart_ram_bank >= 0x08)
                    gb.cart_rtc[gb.cart_ram_bank - 0x08] = val;
                else if (gb.num_ram_banks)
                    gb.gb_cart_ram_write(addr - gb.cart_ram_bank_offset, val);
            }

            return;

        case 0xC:
            gb.wram[addr - WRAM_0_ADDR] = val;
            return;

        case 0xD:
            gb.wram[addr - gb.cgb.wramBankOffset] = val;
            return;

        case 0xE:
            gb.wram[addr - ECHO_ADDR] = val;
            return;

        case 0xF:
            if (addr < OAM_ADDR) {
                gb.wram[(addr - 0x2000) - gb.cgb.wramBankOffset] = val;
                return;
            }

            if (addr < UNUSED_ADDR) {
                gb.oam[addr - OAM_ADDR] = val;
                return;
            }

            /* Unusable memory area. */
            if (addr < IO_ADDR)
                return;

            if (HRAM_ADDR <= addr && addr < INTR_EN_ADDR) {
                gb.hram[addr - IO_ADDR] = val;
                return;
            }

            if ((addr >= 0xFF10) && (addr <= 0xFF3F)) {
                audio_write(addr, val);
                return;
            }
            uint16_t fixPaletteTemp;
            /* IO and Interrupts. */
            switch (addr & 0xFF) {
                /* Joypad */
                case 0x00:
                    /* Only bits 5 and 4 are R/W.
                     * The lower bits are overwritten later, and the two most
                     * significant bits are unused. */
                    gb.gb_reg.P1 = val;

                    /* Direction keys selected */
                    if ((gb.gb_reg.P1 & 0b010000) == 0)
                        gb.gb_reg.P1 |= (gb.direct.joypad >> 4);
                    /* Button keys selected */
                    else
                        gb.gb_reg.P1 |= (gb.direct.joypad & 0x0F);

                    return;

                /* Serial */
                case 0x01:
                    gb.gb_reg.SB = val;
                    return;

                case 0x02:
                    gb.gb_reg.SC = val;
                    return;

                /* Timer Registers */
                case 0x04:
                    gb.gb_reg.DIV = 0x00;
                    return;

                case 0x05:
                    gb.gb_reg.TIMA = val;
                    return;

                case 0x06:
                    gb.gb_reg.TMA = val;
                    return;

                case 0x07:
                    gb.gb_reg.TAC = val;
                    return;

                /* Interrupt Flag Register */
                case 0x0F:
                    gb.gb_reg.IF = (val | 0b11100000);
                    return;

                /* LCD Registers */
                case 0x40:
                    if (((gb.gb_reg.LCDC & LCDC_ENABLE) == 0) &&
                        (val & LCDC_ENABLE)) {
                        gb.counter.lcd_count = 0;
                        gb.lcd_blank = 1;
                    }

                    gb.gb_reg.LCDC = val;

                    /* LY fixed to 0 when LCD turned off. */
                    if ((gb.gb_reg.LCDC & LCDC_ENABLE) == 0) {
                        /* Do not turn off LCD outside of VBLANK. This may
                         * happen due to poor timing in this emulator. */
                        if (gb.lcd_mode != LCD_VBLANK) {
                            gb.gb_reg.LCDC |= LCDC_ENABLE;
                            return;
                        }

                        gb.gb_reg.STAT = (gb.gb_reg.STAT & ~0x03) | LCD_VBLANK;
                        gb.gb_reg.LY = 0;
                        gb.counter.lcd_count = 0;
                    }

                    return;

                case 0x41:
                    gb.gb_reg.STAT = (val & 0b01111000);
                    return;

                case 0x42:
                    gb.gb_reg.SCY = val;
                    return;

                case 0x43:
                    gb.gb_reg.SCX = val;
                    return;

                /* LY (0xFF44) is read only. */
                case 0x45:
                    gb.gb_reg.LYC = val;
                    return;

                /* DMA Register */
                case 0x46:
                    gb.gb_reg.DMA = (val % 0xF1);

                    for (uint8_t i = 0; i < OAM_SIZE; i++)
                        gb.oam[i] = gb_read((gb.gb_reg.DMA << 8) + i);

                    return;

                /* DMG Palette Registers */
                case 0x47:
                    gb.gb_reg.BGP = val;
                    gb.display.bg_palette[0] = (gb.gb_reg.BGP & 0x03);
                    gb.display.bg_palette[1] = (gb.gb_reg.BGP >> 2) & 0x03;
                    gb.display.bg_palette[2] = (gb.gb_reg.BGP >> 4) & 0x03;
                    gb.display.bg_palette[3] = (gb.gb_reg.BGP >> 6) & 0x03;
                    return;

                case 0x48:
                    gb.gb_reg.OBP0 = val;
                    gb.display.sp_palette[0] = (gb.gb_reg.OBP0 & 0x03);
                    gb.display.sp_palette[1] = (gb.gb_reg.OBP0 >> 2) & 0x03;
                    gb.display.sp_palette[2] = (gb.gb_reg.OBP0 >> 4) & 0x03;
                    gb.display.sp_palette[3] = (gb.gb_reg.OBP0 >> 6) & 0x03;
                    return;

                case 0x49:
                    gb.gb_reg.OBP1 = val;
                    gb.display.sp_palette[4] = (gb.gb_reg.OBP1 & 0x03);
                    gb.display.sp_palette[5] = (gb.gb_reg.OBP1 >> 2) & 0x03;
                    gb.display.sp_palette[6] = (gb.gb_reg.OBP1 >> 4) & 0x03;
                    gb.display.sp_palette[7] = (gb.gb_reg.OBP1 >> 6) & 0x03;
                    return;

                /* Window Position Registers */
                case 0x4A:
                    gb.gb_reg.WY = val;
                    return;

                case 0x4B:
                    gb.gb_reg.WX = val;
                    return;

                /* Prepare Speed Switch*/
                case 0x4D:
                    gb.cgb.doubleSpeedPrep = val & 1;
                    return;

                /* CGB VRAM Bank*/
                case 0x4F:
                    gb.cgb.vramBank = val & 0x01;
                    if (gb.cgb.cgbMode) gb.cgb.vramBankOffset = VRAM_ADDR - (gb.cgb.vramBank << 13);
                    return;

                /* Turn off boot ROM */
                case 0x50:
                    gb.gb_bios_enable = 0;
                    return;

                /* DMA Register */
                case 0x51:
                    gb.cgb.dmaSource = (gb.cgb.dmaSource & 0xFF) + (val << 8);
                    return;
                case 0x52:
                    gb.cgb.dmaSource = (gb.cgb.dmaSource & 0xFF00) + val;
                    return;
                case 0x53:
                    gb.cgb.dmaDest = (gb.cgb.dmaDest & 0xFF) + (val << 8);
                    return;
                case 0x54:
                    gb.cgb.dmaDest = (gb.cgb.dmaDest & 0xFF00) + val;
                    return;

                /* DMA Register*/
                case 0x55:
                    gb.cgb.dmaSize = (val & 0x7F) + 1;
                    gb.cgb.dmaMode = val >> 7;
                    // DMA GBC
                    if (gb.cgb.dmaMode) {  // Only transfer if dma is not active (=1) otherwise treat it as a termination
                        if (gb.cgb.cgbMode) {
                            for (int i = 0; i < (gb.cgb.dmaSize << 4); i++) {
                                gb_write(((gb.cgb.dmaDest & 0x1FF0) | 0x8000) + i, gb_read((gb.cgb.dmaSource & 0xFFF0) + i));
                            }
                            gb.cgb.dmaSource += (gb.cgb.dmaSize << 4);
                            gb.cgb.dmaDest += (gb.cgb.dmaSize << 4);
                            gb.cgb.dmaSize = 0;
                        }
                    }
                    gb.cgb.dmaActive = 1;  // set active if it's an HBlank DMA
                    return;

                /* IR Register*/
                case 0x56:
                    gb.hram[0x56] = val;
                    return;

                /* CGB BG Palette Index*/
                case 0x68:
                    gb.cgb.BGPaletteID = val & 0x3F;
                    gb.cgb.BGPaletteInc = val >> 7;
                    return;

                /* CGB BG Palette*/
                case 0x69:
                    gb.cgb.BGPalette[(gb.cgb.BGPaletteID & 0x3F)] = val;
                    fixPaletteTemp = (gb.cgb.BGPalette[(gb.cgb.BGPaletteID & 0x3E) + 1] << 8) + (gb.cgb.BGPalette[(gb.cgb.BGPaletteID & 0x3E)]);
                    gb.cgb.fixPalette[((gb.cgb.BGPaletteID & 0x3E) >> 1)] = ((fixPaletteTemp & 0x7C00) >> 10) | (fixPaletteTemp & 0x03E0) | ((fixPaletteTemp & 0x001F) << 10);  // swap Red and Blue
                    if (gb.cgb.BGPaletteInc) gb.cgb.BGPaletteID = (gb.cgb.BGPaletteID + 1) & 0x3F;
                    return;

                /* CGB OAM Palette Index*/
                case 0x6A:
                    gb.cgb.OAMPaletteID = val & 0x3F;
                    gb.cgb.OAMPaletteInc = val >> 7;
                    return;

                /* CGB OAM Palette*/
                case 0x6B:
                    gb.cgb.OAMPalette[(gb.cgb.OAMPaletteID & 0x3F)] = val;
                    fixPaletteTemp = (gb.cgb.OAMPalette[(gb.cgb.OAMPaletteID & 0x3E) + 1] << 8) + (gb.cgb.OAMPalette[(gb.cgb.OAMPaletteID & 0x3E)]);
                    gb.cgb.fixPalette[0x20 + ((gb.cgb.OAMPaletteID & 0x3E) >> 1)] = ((fixPaletteTemp & 0x7C00) >> 10) | (fixPaletteTemp & 0x03E0) | ((fixPaletteTemp & 0x001F) << 10);  // swap Red and Blue
                    if (gb.cgb.OAMPaletteInc) gb.cgb.OAMPaletteID = (gb.cgb.OAMPaletteID + 1) & 0x3F;
                    return;

                /* CGB WRAM Bank*/
                case 0x70:
                    gb.cgb.wramBank = val;
                    gb.cgb.wramBankOffset = WRAM_1_ADDR - (1 << 12);
                    if (gb.cgb.cgbMode && (gb.cgb.wramBank & 7) > 0) gb.cgb.wramBankOffset = WRAM_1_ADDR - ((gb.cgb.wramBank & 7) << 12);
                    return;

                /* Interrupt Enable Register */
                case 0xFF:
                    gb.gb_reg.IE = val;
                    return;
            }
    }

    (gb.gb_error)(GB_INVALID_WRITE, addr);
}

void finish_gb_cycle(void) {
    uint8_t inst_cycles;
    inst_cycles = 4;  // make this static to remove a dependancy on it
    /* DIV register timing */
    gb.counter.div_count += inst_cycles;

    if (gb.counter.div_count >= DIV_CYCLES) {
        gb.gb_reg.DIV++;
        gb.counter.div_count -= DIV_CYCLES;
    }

    /* Check serial transmission. */
    if (gb.gb_reg.SC & SERIAL_SC_TX_START) {
        /* If new transfer, call TX function. */
        if (gb.counter.serial_count == 0 && gb.gb_serial_tx != NULL)
            (gb.gb_serial_tx)(gb.gb_reg.SB);

        gb.counter.serial_count += inst_cycles;

        /* If it's time to receive byte, call RX function. */
        if (gb.counter.serial_count >= SERIAL_CYCLES) {
            /* If RX can be done, do it. */
            /* If RX failed, do not change SB if using external
             * clock, or set to 0xFF if using internal clock. */
            uint8_t rx;

            if (gb.gb_serial_rx != NULL &&
                (gb.gb_serial_rx(&rx) ==
                 GB_SERIAL_RX_SUCCESS)) {
                gb.gb_reg.SB = rx;

                /* Inform game of serial TX/RX completion. */
                gb.gb_reg.SC &= 0x01;
                gb.gb_reg.IF |= SERIAL_INTR;
            } else if (gb.gb_reg.SC & SERIAL_SC_CLOCK_SRC) {
                /* If using internal clock, and console is not
                 * attached to any external peripheral, shifted
                 * bits are replaced with logic 1. */
                gb.gb_reg.SB = 0xFF;

                /* Inform game of serial TX/RX completion. */
                gb.gb_reg.SC &= 0x01;
                gb.gb_reg.IF |= SERIAL_INTR;
            } else {
                /* If using external clock, and console is not
                 * attached to any external peripheral, bits are
                 * not shifted, so SB is not modified. */
            }

            gb.counter.serial_count = 0;
        }
    }

    /* TIMA register timing */
    /* TODO: Change tac_enable to struct of TAC timer control bits. */
    if (gb.gb_reg.tac_enable) {
        static const uint_fast16_t TAC_CYCLES[4] = {1024, 16, 64, 256};

        gb.counter.tima_count += inst_cycles;

        while (gb.counter.tima_count >= TAC_CYCLES[gb.gb_reg.tac_rate]) {
            gb.counter.tima_count -= TAC_CYCLES[gb.gb_reg.tac_rate];

            if (++gb.gb_reg.TIMA == 0) {
                gb.gb_reg.IF |= TIMER_INTR;
                /* On overflow, set TMA to TIMA. */
                gb.gb_reg.TIMA = gb.gb_reg.TMA;
            }
        }
    }

    /* TODO Check behaviour of LCD during LCD power off state. */
    /* If LCD is off, don't update LCD state. */
    if ((gb.gb_reg.LCDC & LCDC_ENABLE) == 0)
        return;

    /* LCD Timing */
    gb.counter.lcd_count += inst_cycles;

    /* New Scanline */
    if (gb.counter.lcd_count > LCD_LINE_CYCLES) {
        gb.counter.lcd_count -= LCD_LINE_CYCLES;

        /* LYC Update */
        if (gb.gb_reg.LY == gb.gb_reg.LYC) {
            gb.gb_reg.STAT |= STAT_LYC_COINC;

            if (gb.gb_reg.STAT & STAT_LYC_INTR)
                gb.gb_reg.IF |= LCDC_INTR;
        } else
            gb.gb_reg.STAT &= 0xFB;

        /* Next line */
        // gb.gb_reg.LY = (gb.gb_reg.LY + 1) % LCD_VERT_LINES;

        /* VBLANK Start */
        if (gb.gb_reg.LY == LCD_HEIGHT) {
            gb.lcd_mode = LCD_VBLANK;
            // gb.gb_frame = 1;
            gb.gb_reg.IF |= VBLANK_INTR;

            if (gb.gb_reg.STAT & STAT_MODE_1_INTR)
                gb.gb_reg.IF |= LCDC_INTR;

            /* If frame skip is activated, check if we need to draw
             * the frame or skip it. */
            if (gb.direct.frame_skip) {
                gb.display.frame_skip_count =
                    !gb.display.frame_skip_count;
            }

            /* If interlaced is activated, change which lines get
             * updated. Also, only update lines on frames that are
             * actually drawn when frame skip is enabled. */
            if (gb.direct.interlace &&
                (!gb.direct.frame_skip ||
                 gb.display.frame_skip_count)) {
                gb.display.interlace_count =
                    !gb.display.interlace_count;
            }
        }
        /* Normal Line */
        else if (gb.gb_reg.LY < LCD_HEIGHT) {
            if (gb.gb_reg.LY == 0) {
                /* Clear Screen */
                gb.display.WY = gb.gb_reg.WY;
                gb.display.window_clear = 0;
            }

            gb.lcd_mode = LCD_HBLANK;

            if (gb.gb_reg.STAT & STAT_MODE_0_INTR)
                gb.gb_reg.IF |= LCDC_INTR;
        }
    }
    /* OAM access */
    else if (gb.lcd_mode == LCD_HBLANK && gb.counter.lcd_count >= LCD_MODE_2_CYCLES) {
        gb.lcd_mode = LCD_SEARCH_OAM;

        if (gb.gb_reg.STAT & STAT_MODE_2_INTR)
            gb.gb_reg.IF |= LCDC_INTR;
    }
    /* Update LCD */
    else if (gb.lcd_mode == LCD_SEARCH_OAM && gb.counter.lcd_count >= LCD_MODE_3_CYCLES) {
        gb.lcd_mode = LCD_TRANSFER;
    }
}

void gb_draw_line(void) {
    finish_gb_cycle();
    uint8_t pixels[160] = {0};

    /* If LCD not initialised by front-end, don't render anything. */
    if (gb.display.lcd_draw_line == NULL)
        return;

    if (gb.direct.frame_skip && !gb.display.frame_skip_count)
        return;

    uint8_t pixelsPrio[160] = {0};  // do these pixels have priority over OAM?
    /* If interlaced mode is activated, check if we need to draw the current
     * line. */
    if (gb.direct.interlace) {
        if ((gb.display.interlace_count == 0 && (gb.gb_reg.LY & 1) == 0) || (gb.display.interlace_count == 1 && (gb.gb_reg.LY & 1) == 1)) {
            /* Compensate for missing window draw if required. */
            if (gb.gb_reg.LCDC & LCDC_WINDOW_ENABLE && gb.gb_reg.LY >= gb.display.WY && gb.gb_reg.WX <= 166)
                gb.display.window_clear++;

            return;
        }
    }

    /* If background is enabled, draw it. */
    if (gb.gb_reg.LCDC & LCDC_BG_ENABLE) {
        /* Calculate current background line to draw. Constant because
         * this function draws only this one line each time it is
         * called. */
        const uint8_t bg_y = gb.gb_reg.LY + gb.gb_reg.SCY;

        /* Get selected background map address for first tile
         * corresponding to current line.
         * 0x20 (32) is the width of a background tile, and the bit
         * shift is to calculate the address. */
        const uint16_t bg_map =
            ((gb.gb_reg.LCDC & LCDC_BG_MAP) ? VRAM_BMAP_2 : VRAM_BMAP_1) + (bg_y >> 3) * 0x20;

        /* The displays (what the player sees) X coordinate, drawn right
         * to left. */
        uint8_t disp_x = LCD_WIDTH - 1;

        /* The X coordinate to begin drawing the background at. */
        uint8_t bg_x = disp_x + gb.gb_reg.SCX;

        /* Get tile index for current background tile. */
        uint8_t idx = gb.vram[bg_map + (bg_x >> 3)];
        uint8_t idxAtt = gb.vram[bg_map + (bg_x >> 3) + 0x2000];
        /* Y coordinate of tile pixel to draw. */
        const uint8_t py = (bg_y & 0x07);
        /* X coordinate of tile pixel to draw. */
        uint8_t px = 7 - (bg_x & 0x07);

        uint16_t tile;

        /* Select addressing mode. */
        if (gb.gb_reg.LCDC & LCDC_TILE_SELECT)
            tile = VRAM_TILES_1 + idx * 0x10;
        else
            tile = VRAM_TILES_2 + ((idx + 0x80) % 0x100) * 0x10;

        if (gb.cgb.cgbMode && (idxAtt & 0x08)) tile += 0x2000;  // VRAM bank 2
        if (gb.cgb.cgbMode && (idxAtt & 0x40)) tile += 2 * (7 - py);
        if (!gb.cgb.cgbMode || !(idxAtt & 0x40)) tile += 2 * py;

        /* fetch first tile */
        uint8_t t1, t2;
        if (gb.cgb.cgbMode && (idxAtt & 0x20)) {  // Horizantal Flip
            t1 = gb.vram[tile] << px;
            t2 = gb.vram[tile + 1] << px;
        } else {
            t1 = gb.vram[tile] >> px;
            t2 = gb.vram[tile + 1] >> px;
        }
        for (; disp_x != 0xFF; disp_x--) {
            if (px == 8) {
                /* fetch next tile */
                px = 0;
                bg_x = disp_x + gb.gb_reg.SCX;
                idx = gb.vram[bg_map + (bg_x >> 3)];
                idxAtt = gb.vram[bg_map + (bg_x >> 3) + 0x2000];

                if (gb.gb_reg.LCDC & LCDC_TILE_SELECT)
                    tile = VRAM_TILES_1 + idx * 0x10;
                else
                    tile = VRAM_TILES_2 + ((idx + 0x80) % 0x100) * 0x10;

                if (gb.cgb.cgbMode && (idxAtt & 0x08)) tile += 0x2000;  // VRAM bank 2
                if (gb.cgb.cgbMode && (idxAtt & 0x40)) tile += 2 * (7 - py);
                if (!gb.cgb.cgbMode || !(idxAtt & 0x40)) tile += 2 * py;
                t1 = gb.vram[tile];
                t2 = gb.vram[tile + 1];
            }

            /* copy background */
            if (gb.cgb.cgbMode && (idxAtt & 0x20)) {  // Horizantal Flip
                uint8_t c = (((t1 & 0x80) >> 1) | (t2 & 0x80)) >> 6;
                pixels[disp_x] = ((idxAtt & 0x07) << 2) + c;
                pixelsPrio[disp_x] = (idxAtt >> 7);
                t1 = t1 << 1;
                t2 = t2 << 1;
            } else {
                uint8_t c = (t1 & 0x1) | ((t2 & 0x1) << 1);
                if (gb.cgb.cgbMode) {
                    pixels[disp_x] = ((idxAtt & 0x07) << 2) + c;
                    pixelsPrio[disp_x] = (idxAtt >> 7);
                } else {
                    pixels[disp_x] = gb.display.bg_palette[c];
                    pixels[disp_x] |= LCD_PALETTE_BG;
                }
                t1 = t1 >> 1;
                t2 = t2 >> 1;
            }
            px++;
        }
    }

    /* draw window */
    if (gb.gb_reg.LCDC & LCDC_WINDOW_ENABLE && gb.gb_reg.LY >= gb.display.WY && gb.gb_reg.WX <= 166) {
        /* Calculate Window Map Address. */
        uint16_t win_line = (gb.gb_reg.LCDC & LCDC_WINDOW_MAP) ? VRAM_BMAP_2 : VRAM_BMAP_1;
        win_line += (gb.display.window_clear >> 3) * 0x20;

        uint8_t disp_x = LCD_WIDTH - 1;
        uint8_t win_x = disp_x - gb.gb_reg.WX + 7;

        // look up tile
        uint8_t py = gb.display.window_clear & 0x07;
        uint8_t px = 7 - (win_x & 0x07);
        uint8_t idx = gb.vram[win_line + (win_x >> 3)];
        uint8_t idxAtt = gb.vram[win_line + (win_x >> 3) + 0x2000];
        uint16_t tile;

        if (gb.gb_reg.LCDC & LCDC_TILE_SELECT)
            tile = VRAM_TILES_1 + idx * 0x10;
        else
            tile = VRAM_TILES_2 + ((idx + 0x80) % 0x100) * 0x10;

        if (gb.cgb.cgbMode && (idxAtt & 0x08)) tile += 0x2000;  // VRAM bank 2
        if (gb.cgb.cgbMode && (idxAtt & 0x40)) tile += 2 * (7 - py);
        if (!gb.cgb.cgbMode || !(idxAtt & 0x40)) tile += 2 * py;

        // fetch first tile
        uint8_t t1, t2;
        if (gb.cgb.cgbMode && (idxAtt & 0x20)) {  // Horizantal Flip
            t1 = gb.vram[tile] << px;
            t2 = gb.vram[tile + 1] << px;
        } else {
            t1 = gb.vram[tile] >> px;
            t2 = gb.vram[tile + 1] >> px;
        }
        // loop & copy window
        uint8_t end = (gb.gb_reg.WX < 7 ? 0 : gb.gb_reg.WX - 7) - 1;

        for (; disp_x != end; disp_x--) {
            if (px == 8) {
                // fetch next tile
                px = 0;
                win_x = disp_x - gb.gb_reg.WX + 7;
                idx = gb.vram[win_line + (win_x >> 3)];
                idxAtt = gb.vram[win_line + (win_x >> 3) + 0x2000];

                if (gb.gb_reg.LCDC & LCDC_TILE_SELECT)
                    tile = VRAM_TILES_1 + idx * 0x10;
                else
                    tile = VRAM_TILES_2 + ((idx + 0x80) % 0x100) * 0x10;

                if (gb.cgb.cgbMode && (idxAtt & 0x08)) tile += 0x2000;  // VRAM bank 2
                if (gb.cgb.cgbMode && (idxAtt & 0x40)) tile += 2 * (7 - py);
                if (!gb.cgb.cgbMode || !(idxAtt & 0x40)) tile += 2 * py;
                t1 = gb.vram[tile];
                t2 = gb.vram[tile + 1];
            }

            // copy window
            if (idxAtt & 0x20) {  // Horizantal Flip
                uint8_t c = (((t1 & 0x80) >> 1) | (t2 & 0x80)) >> 6;
                pixels[disp_x] = ((idxAtt & 0x07) << 2) + c;
                pixelsPrio[disp_x] = (idxAtt >> 7);
                t1 = t1 << 1;
                t2 = t2 << 1;
            } else {
                uint8_t c = (t1 & 0x1) | ((t2 & 0x1) << 1);
                if (gb.cgb.cgbMode) {
                    pixels[disp_x] = ((idxAtt & 0x07) << 2) + c;
                    pixelsPrio[disp_x] = (idxAtt >> 7);
                } else {
                    pixels[disp_x] = gb.display.bg_palette[c];
                    pixels[disp_x] |= LCD_PALETTE_BG;
                }
                t1 = t1 >> 1;
                t2 = t2 >> 1;
            }
            px++;
        }

        gb.display.window_clear++;  // advance window line
    }

    // draw sprites
    if (gb.gb_reg.LCDC & LCDC_OBJ_ENABLE) {
        uint8_t count = 0;

        for (uint8_t s = NUM_SPRITES - 1;
             s != 0xFF /* && count < MAX_SPRITES_LINE */;
             s--) {
            /* Sprite Y position. */
            uint8_t OY = gb.oam[4 * s + 0];
            /* Sprite X position. */
            uint8_t OX = gb.oam[4 * s + 1];
            /* Sprite Tile/Pattern Number. */
            uint8_t OT = gb.oam[4 * s + 2] & (gb.gb_reg.LCDC & LCDC_OBJ_SIZE ? 0xFE : 0xFF);
            /* Additional attributes. */
            uint8_t OF = gb.oam[4 * s + 3];

            /* If sprite isn't on this line, continue. */
            if (gb.gb_reg.LY +
                        (gb.gb_reg.LCDC & LCDC_OBJ_SIZE ? 0 : 8) >=
                    OY ||
                gb.gb_reg.LY + 16 < OY)
                continue;

            count++;

            /* Continue if sprite not visible. */
            if (OX == 0 || OX >= 168)
                continue;

            // y flip
            uint8_t py = gb.gb_reg.LY - OY + 16;

            if (OF & OBJ_FLIP_Y)
                py = (gb.gb_reg.LCDC & LCDC_OBJ_SIZE ? 15 : 7) - py;

            // fetch the tile
            uint8_t t1, t2;
            if (gb.cgb.cgbMode) {
                t1 = gb.vram[((OF & OBJ_BANK) << 10) + VRAM_TILES_1 + OT * 0x10 + 2 * py];
                t2 = gb.vram[((OF & OBJ_BANK) << 10) + VRAM_TILES_1 + OT * 0x10 + 2 * py + 1];
            } else {
                t1 = gb.vram[VRAM_TILES_1 + OT * 0x10 + 2 * py];
                t2 = gb.vram[VRAM_TILES_1 + OT * 0x10 + 2 * py + 1];
            }

            // handle x flip
            uint8_t dir, start, end, shift;

            if (OF & OBJ_FLIP_X) {
                dir = 1;
                start = (OX < 8 ? 0 : OX - 8);
                end = MIN(OX, LCD_WIDTH);
                shift = 8 - OX + start;
            } else {
                dir = -1;
                start = MIN(OX, LCD_WIDTH) - 1;
                end = (OX < 8 ? 0 : OX - 8) - 1;
                shift = OX - (start + 1);
            }

            // copy tile
            t1 >>= shift;
            t2 >>= shift;

            for (uint8_t disp_x = start; disp_x != end; disp_x += dir) {
                uint8_t c = (t1 & 0x1) | ((t2 & 0x1) << 1);
                // check transparency / sprite overlap / background overlap
                if (gb.cgb.cgbMode && (c && !(pixelsPrio[disp_x] && (pixels[disp_x] & 0x3)) && !((OF & OBJ_PRIORITY) && (pixels[disp_x] & 0x3)))) {
                    /* Set pixel colour. */
                    pixels[disp_x] = ((OF & OBJ_CGB_PALETTE) << 2) + c + 0x20;  // add 0x20 to differentiate from BG
                } else if (c && !(OF & OBJ_PRIORITY && pixels[disp_x] & 0x3)) {
                    /* Set pixel colour. */
                    pixels[disp_x] = (OF & OBJ_PALETTE)
                                         ? gb.display.sp_palette[c + 4]
                                         : gb.display.sp_palette[c];
                    /* Set pixel palette (OBJ0 or OBJ1). */
                    pixels[disp_x] |= (OF & OBJ_PALETTE);
                    /* Deselect BG palette. */
                    pixels[disp_x] &= ~LCD_PALETTE_BG;
                }

                t1 = t1 >> 1;
                t2 = t2 >> 1;
            }
        }
    }

    gb.display.lcd_draw_line(pixels, gb.gb_reg.LY);
}

/**
 * Internal function used to step the CPU.
 */

#include "macros.h"
#include "../../functions.h"

void gb_run_frame(void) {
    uint8_t opcode;
    do {
        gb.gb_frame = 0;
        while (!gb.gb_frame) {
            gb.gb_reg.LY = (gb.gb_reg.LY + 1) % LCD_VERT_LINES;
            if (gb.cpu_reg.pc == 0x18) gb.gb_frame = 1;
            if (gb.cpu_reg.pc < 0x8000) {
                int absAddress = gb.cpu_reg.pc + (gb.cpu_reg.pc < 0x4000 ? 0 : ((gb.selected_rom_bank - 1) * ROM_BANK_SIZE));
                if (convertedFunc[absAddress] != NULL) {
                    // PEEK("");
                    // printf("FUN: %x\n", absAddress);
                    convertedFunc[absAddress]();
                    if (gb.cpu_reg.pc == 0x18) gb_finish_frame();
                    return;
                }
            }
            // PEEK("EMU");
            if (gb.cpu_reg.pc == 0x38 || gb.cpu_reg.pc == 0) exit(0);  // crash
            /* Obtain opcode */
            opcode = (gb.gb_halt ? 0x00 : gb_read(gb.cpu_reg.pc++));

            // if(opcode < 0xFF && gb.cpu_reg.pc -1 < 0x8000 && gb.cpu_reg.hl != 0xFF44) printf("%x: %x hl:%x\n", gb.cpu_reg.pc - 1, opcode, gb.cpu_reg.hl);
            /* Execute opcode */
            switch (opcode) {
                case 0x00:
                    NOP;
                    INC_PC(-1)
                    break;
                case 0x01:
                    LD_BC(imm16);
                    INC_PC(-1)
                    break;
                case 0x02:
                    LD_bc_A;
                    INC_PC(-1)
                    break;
                case 0x03:
                    INC_BC;
                    INC_PC(-1)
                    break;
                case 0x04:
                    INC_B;
                    INC_PC(-1)
                    break;
                case 0x05:
                    DEC_B;
                    INC_PC(-1)
                    break;
                case 0x06:
                    LD_B(imm8);
                    INC_PC(-1)
                    break;
                case 0x07:
                    RLCA;
                    INC_PC(-1)
                    break;
                case 0x08:
                    LD_addr_SP(imm16);
                    INC_PC(-1)
                    break;
                case 0x09:
                    ADD_HL_BC;
                    INC_PC(-1)
                    break;
                case 0x0A:
                    LD_A_bc;
                    INC_PC(-1)
                    break;
                case 0x0B:
                    DEC_BC;
                    INC_PC(-1)
                    break;
                case 0x0C:
                    INC_C;
                    INC_PC(-1)
                    break;
                case 0x0D:
                    DEC_C;
                    INC_PC(-1)
                    break;
                case 0x0E:
                    LD_C(imm8);
                    INC_PC(-1)
                    break;
                case 0x0F:
                    RRCA;
                    INC_PC(-1)
                    break;
                case 0x10: /* STOP */
                    break;
                case 0x11:
                    LD_DE(imm16);
                    INC_PC(-1)
                    break;
                case 0x12:
                    LD_de_A;
                    INC_PC(-1)
                    break;
                case 0x13:
                    INC_DE;
                    INC_PC(-1)
                    break;
                case 0x14:
                    INC_D;
                    INC_PC(-1)
                    break;
                case 0x15:
                    DEC_D;
                    INC_PC(-1)
                    break;
                case 0x16:
                    LD_D(imm8);
                    INC_PC(-1)
                    break;
                case 0x17:
                    RLA;
                    INC_PC(-1)
                    break;
                case 0x18:
                    _JR(imm8);
                    break;
                case 0x19:
                    ADD_HL_DE;
                    INC_PC(-1)
                    break;
                case 0x1A:
                    LD_A_de;
                    INC_PC(-1)
                    break;
                case 0x1B:
                    DEC_DE;
                    INC_PC(-1)
                    break;
                case 0x1C:
                    INC_E;
                    INC_PC(-1)
                    break;
                case 0x1D:
                    DEC_E;
                    INC_PC(-1)
                    break;
                case 0x1E:
                    LD_E(imm8);
                    INC_PC(-1)
                    break;
                case 0x1F:
                    RRA;
                    INC_PC(-1)
                    break;
                case 0x20:
                    _JR_NZ(imm8);
                    break;
                case 0x21:
                    LD_HL(imm16);
                    INC_PC(-1)
                    break;
                case 0x22:
                    LD_hli_A;
                    INC_PC(-1)
                    break;
                case 0x23:
                    INC_HL;
                    INC_PC(-1)
                    break;
                case 0x24:
                    INC_H;
                    INC_PC(-1)
                    break;
                case 0x25:
                    DEC_H;
                    INC_PC(-1)
                    break;
                case 0x26:
                    LD_H(imm8);
                    INC_PC(-1)
                    break;
                case 0x27:
                    DAA;
                    INC_PC(-1)
                    break;
                case 0x28:
                    _JR_Z(imm8);
                    break;
                case 0x29:
                    ADD_HL_HL;
                    INC_PC(-1)
                    break;
                case 0x2A:
                    LD_A_hli;
                    INC_PC(-1)
                    break;
                case 0x2B:
                    DEC_HL;
                    INC_PC(-1)
                    break;
                case 0x2C:
                    INC_L;
                    INC_PC(-1)
                    break;
                case 0x2D:
                    DEC_L;
                    INC_PC(-1)
                    break;
                case 0x2E:
                    LD_L(imm8);
                    INC_PC(-1)
                    break;
                case 0x2F:
                    CPL;
                    INC_PC(-1)
                    break;
                case 0x30:
                    _JR_NC(imm8);
                    break;
                case 0x31:
                    LD_SP(imm16);
                    INC_PC(-1)
                    break;
                case 0x32:
                    LD_hld_A;
                    INC_PC(-1)
                    break;
                case 0x33:
                    INC_SP;
                    INC_PC(-1)
                    break;
                case 0x34:
                    INC_hl;
                    INC_PC(-1)
                    break;
                case 0x35:
                    DEC_hl;
                    INC_PC(-1)
                    break;
                case 0x36:
                    LD_hl(imm8);
                    INC_PC(-1)
                    break;
                case 0x37:
                    SCF;
                    INC_PC(-1)
                    break;
                case 0x38:
                    _JR_C(imm8);
                    break;
                case 0x39:
                    ADD_HL_SP;
                    INC_PC(-1)
                    break;
                case 0x3A:
                    LD_A_hld;
                    INC_PC(-1)
                    break;
                case 0x3B:
                    DEC_SP;
                    INC_PC(-1)
                    break;
                case 0x3C:
                    INC_A;
                    INC_PC(-1)
                    break;
                case 0x3D:
                    DEC_A;
                    INC_PC(-1)
                    break;
                case 0x3E:
                    LD_A(imm8);
                    INC_PC(-1)
                    break;
                case 0x3F:
                    CCF;
                    INC_PC(-1)
                    break;
                case 0x40:
                    LD_B_B;
                    INC_PC(-1)
                    break;
                case 0x41:
                    LD_B_C;
                    INC_PC(-1)
                    break;
                case 0x42:
                    LD_B_D;
                    INC_PC(-1)
                    break;
                case 0x43:
                    LD_B_E;
                    INC_PC(-1)
                    break;
                case 0x44:
                    LD_B_H;
                    INC_PC(-1)
                    break;
                case 0x45:
                    LD_B_L;
                    INC_PC(-1)
                    break;
                case 0x46:
                    LD_B_hl;
                    INC_PC(-1)
                    break;
                case 0x47:
                    LD_B_A;
                    INC_PC(-1)
                    break;
                case 0x48:
                    LD_C_B;
                    INC_PC(-1)
                    break;
                case 0x49:
                    LD_C_C;
                    INC_PC(-1)
                    break;
                case 0x4A:
                    LD_C_D;
                    INC_PC(-1)
                    break;
                case 0x4B:
                    LD_C_E;
                    INC_PC(-1)
                    break;
                case 0x4C:
                    LD_C_H;
                    INC_PC(-1)
                    break;
                case 0x4D:
                    LD_C_L;
                    INC_PC(-1)
                    break;
                case 0x4E:
                    LD_C_hl;
                    INC_PC(-1)
                    break;
                case 0x4F:
                    LD_C_A;
                    INC_PC(-1)
                    break;
                case 0x50:
                    LD_D_B;
                    INC_PC(-1)
                    break;
                case 0x51:
                    LD_D_C;
                    INC_PC(-1)
                    break;
                case 0x52:
                    LD_D_D;
                    INC_PC(-1)
                    break;
                case 0x53:
                    LD_D_E;
                    INC_PC(-1)
                    break;
                case 0x54:
                    LD_D_H;
                    INC_PC(-1)
                    break;
                case 0x55:
                    LD_D_L;
                    INC_PC(-1)
                    break;
                case 0x56:
                    LD_D_hl;
                    INC_PC(-1)
                    break;
                case 0x57:
                    LD_D_A;
                    INC_PC(-1)
                    break;
                case 0x58:
                    LD_E_B;
                    INC_PC(-1)
                    break;
                case 0x59:
                    LD_E_C;
                    INC_PC(-1)
                    break;
                case 0x5A:
                    LD_E_D;
                    INC_PC(-1)
                    break;
                case 0x5B:
                    LD_E_E;
                    INC_PC(-1)
                    break;
                case 0x5C:
                    LD_E_H;
                    INC_PC(-1)
                    break;
                case 0x5D:
                    LD_E_L;
                    INC_PC(-1)
                    break;
                case 0x5E:
                    LD_E_hl;
                    INC_PC(-1)
                    break;
                case 0x5F:
                    LD_E_A;
                    INC_PC(-1)
                    break;
                case 0x60:
                    LD_H_B;
                    INC_PC(-1)
                    break;
                case 0x61:
                    LD_H_C;
                    INC_PC(-1)
                    break;
                case 0x62:
                    LD_H_D;
                    INC_PC(-1)
                    break;
                case 0x63:
                    LD_H_E;
                    INC_PC(-1)
                    break;
                case 0x64:
                    LD_H_H;
                    INC_PC(-1)
                    break;
                case 0x65:
                    LD_H_L;
                    INC_PC(-1)
                    break;
                case 0x66:
                    LD_H_hl;
                    INC_PC(-1)
                    break;
                case 0x67:
                    LD_H_A;
                    INC_PC(-1)
                    break;
                case 0x68:
                    LD_L_B;
                    INC_PC(-1)
                    break;
                case 0x69:
                    LD_L_C;
                    INC_PC(-1)
                    break;
                case 0x6A:
                    LD_L_D;
                    INC_PC(-1)
                    break;
                case 0x6B:
                    LD_L_E;
                    INC_PC(-1)
                    break;
                case 0x6C:
                    LD_L_H;
                    INC_PC(-1)
                    break;
                case 0x6D:
                    LD_L_L;
                    INC_PC(-1)
                    break;
                case 0x6E:
                    LD_L_hl;
                    INC_PC(-1)
                    break;
                case 0x6F:
                    LD_L_A;
                    INC_PC(-1)
                    break;
                case 0x70:
                    LD_hl_B;
                    INC_PC(-1)
                    break;
                case 0x71:
                    LD_hl_C;
                    INC_PC(-1)
                    break;
                case 0x72:
                    LD_hl_D;
                    INC_PC(-1)
                    break;
                case 0x73:
                    LD_hl_E;
                    INC_PC(-1)
                    break;
                case 0x74:
                    LD_hl_H;
                    INC_PC(-1)
                    break;
                case 0x75:
                    LD_hl_L;
                    INC_PC(-1)
                    break;
                case 0x76:
                    LD_hl_hl;
                    INC_PC(-1)
                    break;
                case 0x77:
                    LD_hl_A;
                    INC_PC(-1)
                    break;
                case 0x78:
                    LD_A_B;
                    INC_PC(-1)
                    break;
                case 0x79:
                    LD_A_C;
                    INC_PC(-1)
                    break;
                case 0x7A:
                    LD_A_D;
                    INC_PC(-1)
                    break;
                case 0x7B:
                    LD_A_E;
                    INC_PC(-1)
                    break;
                case 0x7C:
                    LD_A_H;
                    INC_PC(-1)
                    break;
                case 0x7D:
                    LD_A_L;
                    INC_PC(-1)
                    break;
                case 0x7E:
                    LD_A_hl;
                    INC_PC(-1)
                    break;
                case 0x7F:
                    LD_A_A;
                    INC_PC(-1)
                    break;
                case 0x80:
                    ADD_A_B;
                    INC_PC(-1)
                    break;
                case 0x81:
                    ADD_A_C;
                    INC_PC(-1)
                    break;
                case 0x82:
                    ADD_A_D;
                    INC_PC(-1)
                    break;
                case 0x83:
                    ADD_A_E;
                    INC_PC(-1)
                    break;
                case 0x84:
                    ADD_A_H;
                    INC_PC(-1)
                    break;
                case 0x85:
                    ADD_A_L;
                    INC_PC(-1)
                    break;
                case 0x86:
                    ADD_A_hl;
                    INC_PC(-1)
                    break;
                case 0x87:
                    ADD_A_A;
                    INC_PC(-1)
                    break;
                case 0x88:
                    ADC_A_B;
                    INC_PC(-1)
                    break;
                case 0x89:
                    ADC_A_C;
                    INC_PC(-1)
                    break;
                case 0x8A:
                    ADC_A_D;
                    INC_PC(-1)
                    break;
                case 0x8B:
                    ADC_A_E;
                    INC_PC(-1)
                    break;
                case 0x8C:
                    ADC_A_H;
                    INC_PC(-1)
                    break;
                case 0x8D:
                    ADC_A_L;
                    INC_PC(-1)
                    break;
                case 0x8E:
                    ADC_A_hl;
                    INC_PC(-1)
                    break;
                case 0x8F:
                    ADC_A_A;
                    INC_PC(-1)
                    break;
                case 0x90:
                    SUB_A_B;
                    INC_PC(-1)
                    break;
                case 0x91:
                    SUB_A_C;
                    INC_PC(-1)
                    break;
                case 0x92:
                    SUB_A_D;
                    INC_PC(-1)
                    break;
                case 0x93:
                    SUB_A_E;
                    INC_PC(-1)
                    break;
                case 0x94:
                    SUB_A_H;
                    INC_PC(-1)
                    break;
                case 0x95:
                    SUB_A_L;
                    INC_PC(-1)
                    break;
                case 0x96:
                    SUB_A_hl;
                    INC_PC(-1)
                    break;
                case 0x97:
                    SUB_A_A;
                    INC_PC(-1)
                    break;
                case 0x98:
                    SBC_A_B;
                    INC_PC(-1)
                    break;
                case 0x99:
                    SBC_A_C;
                    INC_PC(-1)
                    break;
                case 0x9A:
                    SBC_A_D;
                    INC_PC(-1)
                    break;
                case 0x9B:
                    SBC_A_E;
                    INC_PC(-1)
                    break;
                case 0x9C:
                    SBC_A_H;
                    INC_PC(-1)
                    break;
                case 0x9D:
                    SBC_A_L;
                    INC_PC(-1)
                    break;
                case 0x9E:
                    SBC_A_hl;
                    INC_PC(-1)
                    break;
                case 0x9F:
                    SBC_A_A;
                    INC_PC(-1)
                    break;
                case 0xA0:
                    AND_A_B;
                    INC_PC(-1)
                    break;
                case 0xA1:
                    AND_A_C;
                    INC_PC(-1)
                    break;
                case 0xA2:
                    AND_A_D;
                    INC_PC(-1)
                    break;
                case 0xA3:
                    AND_A_E;
                    INC_PC(-1)
                    break;
                case 0xA4:
                    AND_A_H;
                    INC_PC(-1)
                    break;
                case 0xA5:
                    AND_A_L;
                    INC_PC(-1)
                    break;
                case 0xA6:
                    AND_A_hl;
                    INC_PC(-1)
                    break;
                case 0xA7:
                    AND_A_A;
                    INC_PC(-1)
                    break;
                case 0xA8:
                    XOR_A_B;
                    INC_PC(-1)
                    break;
                case 0xA9:
                    XOR_A_C;
                    INC_PC(-1)
                    break;
                case 0xAA:
                    XOR_A_D;
                    INC_PC(-1)
                    break;
                case 0xAB:
                    XOR_A_E;
                    INC_PC(-1)
                    break;
                case 0xAC:
                    XOR_A_H;
                    INC_PC(-1)
                    break;
                case 0xAD:
                    XOR_A_L;
                    INC_PC(-1)
                    break;
                case 0xAE:
                    XOR_A_hl;
                    INC_PC(-1)
                    break;
                case 0xAF:
                    XOR_A_A;
                    INC_PC(-1)
                    break;
                case 0xB0:
                    OR_A_B;
                    INC_PC(-1)
                    break;
                case 0xB1:
                    OR_A_C;
                    INC_PC(-1)
                    break;
                case 0xB2:
                    OR_A_D;
                    INC_PC(-1)
                    break;
                case 0xB3:
                    OR_A_E;
                    INC_PC(-1)
                    break;
                case 0xB4:
                    OR_A_H;
                    INC_PC(-1)
                    break;
                case 0xB5:
                    OR_A_L;
                    INC_PC(-1)
                    break;
                case 0xB6:
                    OR_A_hl;
                    INC_PC(-1)
                    break;
                case 0xB7:
                    OR_A_A;
                    INC_PC(-1)
                    break;
                case 0xB8:
                    CP_A_B;
                    INC_PC(-1)
                    break;
                case 0xB9:
                    CP_A_C;
                    INC_PC(-1)
                    break;
                case 0xBA:
                    CP_A_D;
                    INC_PC(-1)
                    break;
                case 0xBB:
                    CP_A_E;
                    INC_PC(-1)
                    break;
                case 0xBC:
                    CP_A_H;
                    INC_PC(-1)
                    break;
                case 0xBD:
                    CP_A_L;
                    INC_PC(-1)
                    break;
                case 0xBE:
                    CP_A_hl;
                    INC_PC(-1)
                    break;
                case 0xBF:
                    CP_A_A;
                    INC_PC(-1)
                    break;
                case 0xC0:
                    _RET_NZ;
                    break;
                case 0xC1:
                    POP_BC;
                    INC_PC(-1)
                    break;
                case 0xC2:
                    _JP_NZ(imm16);
                    break;
                case 0xC3:
                    _JP(imm16);
                    break;
                case 0xC4:
                    _CALL_NZ(imm16);
                    break;
                case 0xC5:
                    PUSH_BC;
                    INC_PC(-1)
                    break;
                case 0xC6:
                    ADD_A(imm8);
                    INC_PC(-1)
                    break;
                case 0xC7:
                    _RST(0x00);
                    break;  // RST
                case 0xC8:
                    _RET_Z;
                    break;
                case 0xC9:
                    _RET;
                    break;
                case 0xCA:
                    _JP_Z(imm16);
                    break;
                case 0xCC:
                    _CALL_Z(imm16);
                    break;
                case 0xCD:
                    _CALL(imm16);
                    break;
                case 0xCE:
                    ADC_A(imm8);
                    INC_PC(-1)
                    break;
                case 0xCF:
                    _RST(0x08);
                    break;  // RST
                case 0xD0:
                    _RET_NC;
                    break;
                case 0xD1:
                    POP_DE;
                    INC_PC(-1)
                    break;
                case 0xD2:
                    _JP_NC(imm16);
                    break;
                case 0xD4:
                    _CALL_NC(imm16);
                    break;
                case 0xD5:
                    PUSH_DE;
                    INC_PC(-1)
                    break;
                case 0xD6:
                    SUB_A(imm8);
                    INC_PC(-1)
                    break;
                case 0xD7:
                    _RST(0x10);
                    break;  // RST
                case 0xD8:
                    _RET_C;
                    break;
                case 0xD9:
                    _RETI;
                    break;
                case 0xDA:
                    _JP_C(imm16);
                    break;
                case 0xDC:
                    _CALL_C(imm16);
                    break;
                case 0xDE:
                    SBC_A(imm8);
                    INC_PC(-1)
                    break;
                case 0xDF:
                    _RST(0x18);
                    break;  // RST
                case 0xE0:
                    LDH_addr_A(0xFF00 + imm8);
                    INC_PC(-1)
                    break;
                case 0xE1:
                    POP_HL;
                    INC_PC(-1)
                    break;
                case 0xE2:
                    LDH_c_A;
                    INC_PC(-1)
                    break;
                case 0xE5:
                    PUSH_HL;
                    INC_PC(-1)
                    break;
                case 0xE6:
                    AND_A(imm8);
                    INC_PC(-1)
                    break;
                case 0xE7:
                    _RST(0x20);
                    break;  // RST
                case 0xE8:
                    ADD_SP(imm8);
                    INC_PC(-1)
                    break;
                case 0xE9:
                    _JP_hl;
                    break;
                case 0xEA:
                    LD_addr_A(imm16);
                    INC_PC(-1)
                    break;
                case 0xEE:
                    XOR_A(imm8);
                    INC_PC(-1)
                    break;
                case 0xEF:
                    _RST(0x28);
                    break;  // RST
                case 0xF0:
                    LDH_A_addr(0xFF00 + imm8);
                    INC_PC(-1)
                    break;
                case 0xF1:
                    POP_AF;
                    INC_PC(-1)
                    break;
                case 0xF2:
                    LDH_A_c;
                    INC_PC(-1)
                    break;
                case 0xF3: /* DI */
                    break;
                case 0xF5:
                    PUSH_AF;
                    INC_PC(-1)
                    break;
                case 0xF6:
                    OR_A(imm8);
                    INC_PC(-1)
                    break;
                case 0xF7:
                    _RST(0x30);
                    break;  // RST
                case 0xF8:
                    LD_HL_SP(imm8);
                    INC_PC(-1)
                    break;
                case 0xF9:
                    LD_SP_HL;
                    INC_PC(-1)
                    break;
                case 0xFA:
                    LD_A_addr(imm16);
                    INC_PC(-1)
                    break;
                case 0xFB: /* EI */
                    break;
                case 0xFE:
                    CP_A(imm8);
                    INC_PC(-1)
                    break;
                case 0xFF:
                    _RST(0x38);
                    break;  // RST
                case 0xCB:  /* CB INST */
                    switch (gb_read(gb.cpu_reg.pc++)) {
                        case 0x00:
                            RLC_B;
                            break;
                        case 0x01:
                            RLC_C;
                            break;
                        case 0x02:
                            RLC_D;
                            break;
                        case 0x03:
                            RLC_E;
                            break;
                        case 0x04:
                            RLC_H;
                            break;
                        case 0x05:
                            RLC_L;
                            break;
                        case 0x06:
                            RLC_hl;
                            break;
                        case 0x07:
                            RLC_A;
                            break;
                        case 0x08:
                            RRC_B;
                            break;
                        case 0x09:
                            RRC_C;
                            break;
                        case 0x0A:
                            RRC_D;
                            break;
                        case 0x0B:
                            RRC_E;
                            break;
                        case 0x0C:
                            RRC_H;
                            break;
                        case 0x0D:
                            RRC_L;
                            break;
                        case 0x0E:
                            RRC_hl;
                            break;
                        case 0x0F:
                            RRC_A;
                            break;
                        case 0x10:
                            RL_B;
                            break;
                        case 0x11:
                            RL_C;
                            break;
                        case 0x12:
                            RL_D;
                            break;
                        case 0x13:
                            RL_E;
                            break;
                        case 0x14:
                            RL_H;
                            break;
                        case 0x15:
                            RL_L;
                            break;
                        case 0x16:
                            RL_hl;
                            break;
                        case 0x17:
                            RL_A;
                            break;
                        case 0x18:
                            RR_B;
                            break;
                        case 0x19:
                            RR_C;
                            break;
                        case 0x1A:
                            RR_D;
                            break;
                        case 0x1B:
                            RR_E;
                            break;
                        case 0x1C:
                            RR_H;
                            break;
                        case 0x1D:
                            RR_L;
                            break;
                        case 0x1E:
                            RR_hl;
                            break;
                        case 0x1F:
                            RR_A;
                            break;
                        case 0x20:
                            SLA_B;
                            break;
                        case 0x21:
                            SLA_C;
                            break;
                        case 0x22:
                            SLA_D;
                            break;
                        case 0x23:
                            SLA_E;
                            break;
                        case 0x24:
                            SLA_H;
                            break;
                        case 0x25:
                            SLA_L;
                            break;
                        case 0x26:
                            SLA_hl;
                            break;
                        case 0x27:
                            SLA_A;
                            break;
                        case 0x28:
                            SRA_B;
                            break;
                        case 0x29:
                            SRA_C;
                            break;
                        case 0x2A:
                            SRA_D;
                            break;
                        case 0x2B:
                            SRA_E;
                            break;
                        case 0x2C:
                            SRA_H;
                            break;
                        case 0x2D:
                            SRA_L;
                            break;
                        case 0x2E:
                            SRA_hl;
                            break;
                        case 0x2F:
                            SRA_A;
                            break;
                        case 0x30:
                            SWAP_B;
                            break;
                        case 0x31:
                            SWAP_C;
                            break;
                        case 0x32:
                            SWAP_D;
                            break;
                        case 0x33:
                            SWAP_E;
                            break;
                        case 0x34:
                            SWAP_H;
                            break;
                        case 0x35:
                            SWAP_L;
                            break;
                        case 0x36:
                            SWAP_hl;
                            break;
                        case 0x37:
                            SWAP_A;
                            break;
                        case 0x38:
                            SRL_B;
                            break;
                        case 0x39:
                            SRL_C;
                            break;
                        case 0x3A:
                            SRL_D;
                            break;
                        case 0x3B:
                            SRL_E;
                            break;
                        case 0x3C:
                            SRL_H;
                            break;
                        case 0x3D:
                            SRL_L;
                            break;
                        case 0x3E:
                            SRL_hl;
                            break;
                        case 0x3F:
                            SRL_A;
                            break;
                        case 0x40:
                            BIT_B(0);
                            break;
                        case 0x41:
                            BIT_C(0);
                            break;
                        case 0x42:
                            BIT_D(0);
                            break;
                        case 0x43:
                            BIT_E(0);
                            break;
                        case 0x44:
                            BIT_H(0);
                            break;
                        case 0x45:
                            BIT_L(0);
                            break;
                        case 0x46:
                            BIT_hl(0);
                            break;
                        case 0x47:
                            BIT_A(0);
                            break;
                        case 0x48:
                            BIT_B(1);
                            break;
                        case 0x49:
                            BIT_C(1);
                            break;
                        case 0x4A:
                            BIT_D(1);
                            break;
                        case 0x4B:
                            BIT_E(1);
                            break;
                        case 0x4C:
                            BIT_H(1);
                            break;
                        case 0x4D:
                            BIT_L(1);
                            break;
                        case 0x4E:
                            BIT_hl(1);
                            break;
                        case 0x4F:
                            BIT_A(1);
                            break;
                        case 0x50:
                            BIT_B(2);
                            break;
                        case 0x51:
                            BIT_C(2);
                            break;
                        case 0x52:
                            BIT_D(2);
                            break;
                        case 0x53:
                            BIT_E(2);
                            break;
                        case 0x54:
                            BIT_H(2);
                            break;
                        case 0x55:
                            BIT_L(2);
                            break;
                        case 0x56:
                            BIT_hl(2);
                            break;
                        case 0x57:
                            BIT_A(2);
                            break;
                        case 0x58:
                            BIT_B(3);
                            break;
                        case 0x59:
                            BIT_C(3);
                            break;
                        case 0x5A:
                            BIT_D(3);
                            break;
                        case 0x5B:
                            BIT_E(3);
                            break;
                        case 0x5C:
                            BIT_H(3);
                            break;
                        case 0x5D:
                            BIT_L(3);
                            break;
                        case 0x5E:
                            BIT_hl(3);
                            break;
                        case 0x5F:
                            BIT_A(3);
                            break;
                        case 0x60:
                            BIT_B(4);
                            break;
                        case 0x61:
                            BIT_C(4);
                            break;
                        case 0x62:
                            BIT_D(4);
                            break;
                        case 0x63:
                            BIT_E(4);
                            break;
                        case 0x64:
                            BIT_H(4);
                            break;
                        case 0x65:
                            BIT_L(4);
                            break;
                        case 0x66:
                            BIT_hl(4);
                            break;
                        case 0x67:
                            BIT_A(4);
                            break;
                        case 0x68:
                            BIT_B(5);
                            break;
                        case 0x69:
                            BIT_C(5);
                            break;
                        case 0x6A:
                            BIT_D(5);
                            break;
                        case 0x6B:
                            BIT_E(5);
                            break;
                        case 0x6C:
                            BIT_H(5);
                            break;
                        case 0x6D:
                            BIT_L(5);
                            break;
                        case 0x6E:
                            BIT_hl(5);
                            break;
                        case 0x6F:
                            BIT_A(5);
                            break;
                        case 0x70:
                            BIT_B(6);
                            break;
                        case 0x71:
                            BIT_C(6);
                            break;
                        case 0x72:
                            BIT_D(6);
                            break;
                        case 0x73:
                            BIT_E(6);
                            break;
                        case 0x74:
                            BIT_H(6);
                            break;
                        case 0x75:
                            BIT_L(6);
                            break;
                        case 0x76:
                            BIT_hl(6);
                            break;
                        case 0x77:
                            BIT_A(6);
                            break;
                        case 0x78:
                            BIT_B(7);
                            break;
                        case 0x79:
                            BIT_C(7);
                            break;
                        case 0x7A:
                            BIT_D(7);
                            break;
                        case 0x7B:
                            BIT_E(7);
                            break;
                        case 0x7C:
                            BIT_H(7);
                            break;
                        case 0x7D:
                            BIT_L(7);
                            break;
                        case 0x7E:
                            BIT_hl(7);
                            break;
                        case 0x7F:
                            BIT_A(7);
                            break;
                        case 0x80:
                            RES_B(0);
                            break;
                        case 0x81:
                            RES_C(0);
                            break;
                        case 0x82:
                            RES_D(0);
                            break;
                        case 0x83:
                            RES_E(0);
                            break;
                        case 0x84:
                            RES_H(0);
                            break;
                        case 0x85:
                            RES_L(0);
                            break;
                        case 0x86:
                            RES_hl(0);
                            break;
                        case 0x87:
                            RES_A(0);
                            break;
                        case 0x88:
                            RES_B(1);
                            break;
                        case 0x89:
                            RES_C(1);
                            break;
                        case 0x8A:
                            RES_D(1);
                            break;
                        case 0x8B:
                            RES_E(1);
                            break;
                        case 0x8C:
                            RES_H(1);
                            break;
                        case 0x8D:
                            RES_L(1);
                            break;
                        case 0x8E:
                            RES_hl(1);
                            break;
                        case 0x8F:
                            RES_A(1);
                            break;
                        case 0x90:
                            RES_B(2);
                            break;
                        case 0x91:
                            RES_C(2);
                            break;
                        case 0x92:
                            RES_D(2);
                            break;
                        case 0x93:
                            RES_E(2);
                            break;
                        case 0x94:
                            RES_H(2);
                            break;
                        case 0x95:
                            RES_L(2);
                            break;
                        case 0x96:
                            RES_hl(2);
                            break;
                        case 0x97:
                            RES_A(2);
                            break;
                        case 0x98:
                            RES_B(3);
                            break;
                        case 0x99:
                            RES_C(3);
                            break;
                        case 0x9A:
                            RES_D(3);
                            break;
                        case 0x9B:
                            RES_E(3);
                            break;
                        case 0x9C:
                            RES_H(3);
                            break;
                        case 0x9D:
                            RES_L(3);
                            break;
                        case 0x9E:
                            RES_hl(3);
                            break;
                        case 0x9F:
                            RES_A(3);
                            break;
                        case 0xA0:
                            RES_B(4);
                            break;
                        case 0xA1:
                            RES_C(4);
                            break;
                        case 0xA2:
                            RES_D(4);
                            break;
                        case 0xA3:
                            RES_E(4);
                            break;
                        case 0xA4:
                            RES_H(4);
                            break;
                        case 0xA5:
                            RES_L(4);
                            break;
                        case 0xA6:
                            RES_hl(4);
                            break;
                        case 0xA7:
                            RES_A(4);
                            break;
                        case 0xA8:
                            RES_B(5);
                            break;
                        case 0xA9:
                            RES_C(5);
                            break;
                        case 0xAA:
                            RES_D(5);
                            break;
                        case 0xAB:
                            RES_E(5);
                            break;
                        case 0xAC:
                            RES_H(5);
                            break;
                        case 0xAD:
                            RES_L(5);
                            break;
                        case 0xAE:
                            RES_hl(5);
                            break;
                        case 0xAF:
                            RES_A(5);
                            break;
                        case 0xB0:
                            RES_B(6);
                            break;
                        case 0xB1:
                            RES_C(6);
                            break;
                        case 0xB2:
                            RES_D(6);
                            break;
                        case 0xB3:
                            RES_E(6);
                            break;
                        case 0xB4:
                            RES_H(6);
                            break;
                        case 0xB5:
                            RES_L(6);
                            break;
                        case 0xB6:
                            RES_hl(6);
                            break;
                        case 0xB7:
                            RES_A(6);
                            break;
                        case 0xB8:
                            RES_B(7);
                            break;
                        case 0xB9:
                            RES_C(7);
                            break;
                        case 0xBA:
                            RES_D(7);
                            break;
                        case 0xBB:
                            RES_E(7);
                            break;
                        case 0xBC:
                            RES_H(7);
                            break;
                        case 0xBD:
                            RES_L(7);
                            break;
                        case 0xBE:
                            RES_hl(7);
                            break;
                        case 0xBF:
                            RES_A(7);
                            break;
                        case 0xC0:
                            SET_B(0);
                            break;
                        case 0xC1:
                            SET_C(0);
                            break;
                        case 0xC2:
                            SET_D(0);
                            break;
                        case 0xC3:
                            SET_E(0);
                            break;
                        case 0xC4:
                            SET_H(0);
                            break;
                        case 0xC5:
                            SET_L(0);
                            break;
                        case 0xC6:
                            SET_hl(0);
                            break;
                        case 0xC7:
                            SET_A(0);
                            break;
                        case 0xC8:
                            SET_B(1);
                            break;
                        case 0xC9:
                            SET_C(1);
                            break;
                        case 0xCA:
                            SET_D(1);
                            break;
                        case 0xCB:
                            SET_E(1);
                            break;
                        case 0xCC:
                            SET_H(1);
                            break;
                        case 0xCD:
                            SET_L(1);
                            break;
                        case 0xCE:
                            SET_hl(1);
                            break;
                        case 0xCF:
                            SET_A(1);
                            break;
                        case 0xD0:
                            SET_B(2);
                            break;
                        case 0xD1:
                            SET_C(2);
                            break;
                        case 0xD2:
                            SET_D(2);
                            break;
                        case 0xD3:
                            SET_E(2);
                            break;
                        case 0xD4:
                            SET_H(2);
                            break;
                        case 0xD5:
                            SET_L(2);
                            break;
                        case 0xD6:
                            SET_hl(2);
                            break;
                        case 0xD7:
                            SET_A(2);
                            break;
                        case 0xD8:
                            SET_B(3);
                            break;
                        case 0xD9:
                            SET_C(3);
                            break;
                        case 0xDA:
                            SET_D(3);
                            break;
                        case 0xDB:
                            SET_E(3);
                            break;
                        case 0xDC:
                            SET_H(3);
                            break;
                        case 0xDD:
                            SET_L(3);
                            break;
                        case 0xDE:
                            SET_hl(3);
                            break;
                        case 0xDF:
                            SET_A(3);
                            break;
                        case 0xE0:
                            SET_B(4);
                            break;
                        case 0xE1:
                            SET_C(4);
                            break;
                        case 0xE2:
                            SET_D(4);
                            break;
                        case 0xE3:
                            SET_E(4);
                            break;
                        case 0xE4:
                            SET_H(4);
                            break;
                        case 0xE5:
                            SET_L(4);
                            break;
                        case 0xE6:
                            SET_hl(4);
                            break;
                        case 0xE7:
                            SET_A(4);
                            break;
                        case 0xE8:
                            SET_B(5);
                            break;
                        case 0xE9:
                            SET_C(5);
                            break;
                        case 0xEA:
                            SET_D(5);
                            break;
                        case 0xEB:
                            SET_E(5);
                            break;
                        case 0xEC:
                            SET_H(5);
                            break;
                        case 0xED:
                            SET_L(5);
                            break;
                        case 0xEE:
                            SET_hl(5);
                            break;
                        case 0xEF:
                            SET_A(5);
                            break;
                        case 0xF0:
                            SET_B(6);
                            break;
                        case 0xF1:
                            SET_C(6);
                            break;
                        case 0xF2:
                            SET_D(6);
                            break;
                        case 0xF3:
                            SET_E(6);
                            break;
                        case 0xF4:
                            SET_H(6);
                            break;
                        case 0xF5:
                            SET_L(6);
                            break;
                        case 0xF6:
                            SET_hl(6);
                            break;
                        case 0xF7:
                            SET_A(6);
                            break;
                        case 0xF8:
                            SET_B(7);
                            break;
                        case 0xF9:
                            SET_C(7);
                            break;
                        case 0xFA:
                            SET_D(7);
                            break;
                        case 0xFB:
                            SET_E(7);
                            break;
                        case 0xFC:
                            SET_H(7);
                            break;
                        case 0xFD:
                            SET_L(7);
                            break;
                        case 0xFE:
                            SET_hl(7);
                            break;
                        case 0xFF:
                            SET_A(7);
                            break;
                    }
                    INC_PC(-2)
                    break;

                default:
                    (gb.gb_error)(GB_INVALID_OPCODE, opcode);
            }
        }
        gb_finish_frame();
    } while (gb.redirected);
}

void gb_finish_frame(void) {
    for (int line = 0; line < 144; line++) {
        gb.gb_reg.LY = line;
        LCD();
        gb_draw_line();
    }
    sdl_loop();
}

/**
 * Gets the size of the save file required for the ROM.
 */
uint_fast32_t gb_get_save_size(void) {
    const uint_fast16_t ram_size_location = 0x0149;
    const uint_fast32_t ram_sizes[] =
        {
            0x00, 0x800, 0x2000, 0x8000, 0x20000};
    uint8_t ram_size = gb.gb_rom_read(ram_size_location);
    return ram_sizes[ram_size];
}

/**
 * Set the function used to handle serial transfer in the front-end. This is
 * optional.
 * gb_serial_transfer takes a byte to transmit and returns the received byte. If
 * no cable is connected to the console, return 0xFF.
 */
void gb_init_serial(
    void (*gb_serial_tx)(const uint8_t),
    enum gb_serial_rx_ret_e (*gb_serial_rx)(struct gb_s *,
                                            uint8_t *)) {
    gb.gb_serial_tx = gb_serial_tx;
    gb.gb_serial_rx = (void *)gb_serial_rx;
}

uint8_t gb_colour_hash(void) {
#define ROM_TITLE_START_ADDR 0x0134
#define ROM_TITLE_END_ADDR 0x0143

    uint8_t x = 0;

    for (uint16_t i = ROM_TITLE_START_ADDR; i <= ROM_TITLE_END_ADDR; i++)
        x += gb.gb_rom_read(i);

    return x;
}

/**
 * Resets the context, and initialises startup values.
 */
void gb_reset(void) {
    init_function_pointers();
    hram = (struct hram_s*)gb.hram;
    vram = (struct vram_s*)gb.vram;

    gb.gb_halt = 0;
    gb.gb_ime = 1;
    gb.gb_bios_enable = 0;
    gb.lcd_mode = LCD_HBLANK;

    /* Initialise MBC values. */
    gb.selected_rom_bank = 1;
    gb.cart_ram_bank = 0;
    gb.enable_cart_ram = 0;
    gb.cart_mode_select = 0;

    /* Initialise CPU registers as though a DMG or CGB. */
    gb.cpu_reg.af = 0x01B0;
    if (gb.cgb.cgbMode) gb.cpu_reg.af = 0x1180;
    gb.cpu_reg.bc = 0x0013;
    if (gb.cgb.cgbMode) gb.cpu_reg.bc = 0x0000;
    gb.cpu_reg.de = 0x00D8;
    if (gb.cgb.cgbMode) gb.cpu_reg.de = 0x0008;
    gb.cpu_reg.hl = 0x014D;
    if (gb.cgb.cgbMode) gb.cpu_reg.hl = 0x007C;
    gb.cpu_reg.sp = 0xFFFE;
    /* TODO: Add BIOS support. */
    gb.cpu_reg.pc = 0x0100;

    gb.counter.lcd_count = 0;
    gb.counter.div_count = 0;
    gb.counter.tima_count = 0;
    gb.counter.serial_count = 0;

    gb.gb_reg.TIMA = 0x00;
    gb.gb_reg.TMA = 0x00;
    gb.gb_reg.TAC = 0xF8;
    gb.gb_reg.DIV = 0xAB;
    if (gb.cgb.cgbMode) gb.gb_reg.DIV = 0xFF;

    gb.gb_reg.IF = 0xE1;

    gb.gb_reg.LCDC = 0x91;
    gb.gb_reg.SCY = 0x00;
    gb.gb_reg.SCX = 0x00;
    gb.gb_reg.LYC = 0x00;

    /* Appease valgrind for invalid reads and unconditional jumps. */
    gb.gb_reg.SC = 0x7E;
    if (gb.cgb.cgbMode) gb.gb_reg.SC = 0x7F;
    gb.gb_reg.STAT = 0x85;
    gb.gb_reg.LY = 0;

    /* Initialize some CGB registers */
    gb.cgb.doubleSpeed = 0;
    gb.cgb.doubleSpeedPrep = 0;
    gb.cgb.wramBank = 1;
    gb.cgb.wramBankOffset = WRAM_0_ADDR;
    gb.cgb.vramBank = 0;
    gb.cgb.vramBankOffset = VRAM_ADDR;
    for (int i = 0; i < 0x20; i++) {
        gb.cgb.OAMPalette[(i << 1)] = gb.cgb.BGPalette[(i << 1)] = 0x7F;
        gb.cgb.OAMPalette[(i << 1) + 1] = gb.cgb.BGPalette[(i << 1) + 1] = 0xFF;
    }
    gb.cgb.OAMPaletteID = 0;
    gb.cgb.BGPaletteID = 0;
    gb.cgb.OAMPaletteInc = 0;
    gb.cgb.BGPaletteInc = 0;
    gb.cgb.dmaActive = 1;  // Not active
    gb.cgb.dmaMode = 0;
    gb.cgb.dmaSize = 0;
    gb.cgb.dmaSource = 0;
    gb.cgb.dmaDest = 0;

    gb_write(0xFF47, 0xFC);  // BGP
    gb_write(0xFF48, 0xFF);  // OBJP0
    gb_write(0xFF49, 0x0F);  // OBJP1
    gb.gb_reg.WY = 0x00;
    gb.gb_reg.WX = 0x00;
    gb.gb_reg.IE = 0x00;

    gb.direct.joypad = 0xFF;
    gb.gb_reg.P1 = 0xCF;

    gb.redirected = 1;  // set to 1 to use the alternative (broken) emulation method
    gb.calledEmu = 0;   // set to 1 if calling the emulator FROM redirected code
    for (int i = 0; i < STACK_CALL_SIZE; i++) gb.stackCalls[i] = 0;
    gb.stackDepth = 0;
    gb.nestedCalls = 0;
}

/**
 * Initialise the emulator context. gb_reset() is also called to initialise
 * the CPU.
 */
enum gb_init_error_e gb_init(
    uint8_t (*gb_rom_read)(const uint_fast32_t),
    uint8_t (*gb_cart_ram_read)(const uint_fast32_t),
    void (*gb_cart_ram_write)(const uint_fast32_t, const uint8_t),
    void (*gb_error)(const enum gb_error_e, const uint16_t),
    void *priv) {
    const uint16_t cgb_flag = 0x0143;
    const uint16_t mbc_location = 0x0147;
    const uint16_t bank_count_location = 0x0148;
    const uint16_t ram_size_location = 0x0149;
    /**
     * Table for cartridge type (MBC). -1 if invalid.
     * TODO: MMM01 is untested.
     * TODO: MBC6 is untested.
     * TODO: MBC7 is unsupported.
     * TODO: POCKET CAMERA is unsupported.
     * TODO: BANDAI TAMA5 is unsupported.
     * TODO: HuC3 is unsupported.
     * TODO: HuC1 is unsupported.
     **/
    const uint8_t cart_mbc[] =
        {
            0, 1, 1, 1, -1, 2, 2, -1, 0, 0, -1, 0, 0, 0, -1, 3,
            3, 3, 3, 3, -1, -1, -1, -1, -1, 5, 5, 5, 5, 5, 5, -1};
    const uint8_t cart_ram[] =
        {
            0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
            1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0};
    const uint16_t num_rom_banks_mask[] =
        {
            2, 4, 8, 16, 32, 64, 128, 256, 512, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 72, 80, 96, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    const uint8_t num_ram_banks[] = {0, 1, 1, 4, 16, 8};

    gb.gb_rom_read = gb_rom_read;
    gb.gb_cart_ram_read = gb_cart_ram_read;
    gb.gb_cart_ram_write = gb_cart_ram_write;
    gb.gb_error = gb_error;
    gb.direct.priv = priv;

    /* Initialise serial transfer function to NULL. If the front-end does
     * not provide serial support, Peanut-GB will emulate no cable connected
     * automatically. */
    gb.gb_serial_tx = NULL;
    gb.gb_serial_rx = NULL;

    /* Check valid ROM using checksum value. */
    {
        uint8_t x = 0;

        for (uint16_t i = 0x0134; i <= 0x014C; i++)
            x = x - gb.gb_rom_read(i) - 1;

        if (x != gb.gb_rom_read(ROM_HEADER_CHECKSUM_LOC))
            return GB_INIT_INVALID_CHECKSUM;
    }

    /* Check if cartridge type is supported, and set MBC type. */
    {
        gb.cgb.cgbMode = (gb.gb_rom_read(cgb_flag) & 0x80) >> 7;
        const uint8_t mbc_value = gb.gb_rom_read(mbc_location);

        if (mbc_value > sizeof(cart_mbc) - 1 ||
            (gb.mbc = cart_mbc[mbc_value]) == 255u)
            return GB_INIT_CARTRIDGE_UNSUPPORTED;
    }

    gb.cart_ram = cart_ram[gb.gb_rom_read(mbc_location)];
    gb.num_rom_banks_mask = num_rom_banks_mask[gb.gb_rom_read(bank_count_location)] - 1;
    gb.num_ram_banks = num_ram_banks[gb.gb_rom_read(ram_size_location)];

    gb.lcd_blank = 0;
    gb.display.lcd_draw_line = NULL;

    gb_reset();

    return GB_INIT_NO_ERROR;
}

/**
 * Returns the title of ROM.
 *
 * \param gb        Initialised context.
 * \param title_str    Allocated string at least 16 characters.
 * \returns        Pointer to start of string, null terminated.
 */
const char *gb_get_rom_name(char *title_str) {
    uint_fast16_t title_loc = 0x134;
    /* End of title may be 0x13E for newer games. */
    const uint_fast16_t title_end = 0x143;
    const char *title_start = title_str;

    for (; title_loc <= title_end; title_loc++) {
        const char title_char = gb.gb_rom_read(title_loc);

        if (title_char >= ' ' && title_char <= '_') {
            *title_str = title_char;
            title_str++;
        } else
            break;
    }

    *title_str = '\0';
    return title_start;
}

void gb_init_lcd(
    void (*lcd_draw_line)(
        const uint8_t *pixels,
        const uint_fast8_t line)) {
    gb.display.lcd_draw_line = lcd_draw_line;

    gb.direct.interlace = 0;
    gb.display.interlace_count = 0;
    gb.direct.frame_skip = 0;
    gb.display.frame_skip_count = 0;

    gb.display.window_clear = 0;
    gb.display.WY = 0;

    return;
}

/**
 * Returns a byte from the ROM file at the given address.
 */
uint8_t gb_rom_read(const uint_fast32_t addr) {
    const struct priv_t *const p = gb.direct.priv;
    return p->rom[addr];
}

/**
 * Returns a byte from the cartridge RAM at the given address.
 */
uint8_t gb_cart_ram_read(const uint_fast32_t addr) {
    const struct priv_t *const p = gb.direct.priv;
    return p->cart_ram[addr];
}

/**
 * Writes a given byte to the cartridge RAM at the given address.
 */
void gb_cart_ram_write(const uint_fast32_t addr,
                       const uint8_t val) {
    const struct priv_t *const p = gb.direct.priv;
    p->cart_ram[addr] = val;
}

/**
 * Returns a pointer to the allocated space containing the ROM. Must be freed.
 */
uint8_t *read_rom_to_ram(const char *file_name) {
    FILE *rom_file = fopen(file_name, "rb");
    size_t rom_size;
    uint8_t *rom = NULL;

    if (rom_file == NULL)
        return NULL;

    fseek(rom_file, 0, SEEK_END);
    rom_size = ftell(rom_file);
    rewind(rom_file);
    rom = malloc(rom_size);

    if (fread(rom, sizeof(uint8_t), rom_size, rom_file) != rom_size) {
        free(rom);
        fclose(rom_file);
        return NULL;
    }

    fclose(rom_file);
    return rom;
}

void read_cart_ram_file(const char *save_file_name, uint8_t **dest,
                        const size_t len) {
    FILE *f;

    /* If save file not required. */
    if (len == 0) {
        *dest = NULL;
        return;
    }

    /* Allocate enough memory to hold save file. */
    if ((*dest = malloc(len)) == NULL) {
        printf("%d: %s\n", __LINE__, strerror(errno));
        exit(EXIT_FAILURE);
    }

    f = fopen(save_file_name, "rb");

    /* It doesn't matter if the save file doesn't exist. We initialise the
     * save memory allocated above. The save file will be created on exit. */
    if (f == NULL) {
        memset(*dest, 0, len);
        return;
    }

    /* Read save file to allocated memory. */
    if (fread(*dest, sizeof(uint8_t), len, f)) printf("Save loaded\n");
    fclose(f);
}

void write_cart_ram_file(const char *save_file_name, uint8_t **dest,
                         const size_t len) {
    FILE *f;

    if (len == 0 || *dest == NULL)
        return;

    if ((f = fopen(save_file_name, "wb")) == NULL) {
        puts("Unable to open save file.");
        printf("%d: %s\n", __LINE__, strerror(errno));
        exit(EXIT_FAILURE);
    }

    /* Record save file. */
    fwrite(*dest, sizeof(uint8_t), len, f);
    fclose(f);
}

/**
 * Handles an error reported by the emulator. The emulator context may be used
 * to better understand why the error given in gb_err was reported.
 */
void gb_error(const enum gb_error_e gb_err, const uint16_t val) {
    struct priv_t *priv = gb.direct.priv;

    switch (gb_err) {
        case GB_INVALID_OPCODE:
            /* We compensate for the post-increment in the gb_step_cpu
             * function. */
            fprintf(stdout, "Invalid opcode %#04x at PC: %#06x, SP: %#06x\n",
                    val,
                    gb.cpu_reg.pc - 1,
                    gb.cpu_reg.sp);
            break;

        /* Ignoring non fatal errors. */
        case GB_INVALID_WRITE:
        case GB_INVALID_READ:
            return;

        default:
            printf("Unknown error");
            break;
    }

    fprintf(stderr, "Error. Press q to exit, or any other key to continue.");

    if (getchar() == 'q') {
        /* Record save file. */
        write_cart_ram_file("recovery.sav", &priv->cart_ram,
                            gb_get_save_size());

        free(priv->rom);
        free(priv->cart_ram);
        exit(EXIT_FAILURE);
    }

    return;
}

/**
 * Draws scanline into framebuffer.
 */
void lcd_draw_line(const uint8_t pixels[160],
                   const uint_least8_t line) {
    struct priv_t *priv = gb.direct.priv;
    if (gb.cgb.cgbMode) {  // CGB
        for (unsigned int x = 0; x < LCD_WIDTH; x++) {
            priv->fb[line][x] = gb.cgb.fixPalette[pixels[x]];
        }
    } else {  // DMG
        for (unsigned int x = 0; x < LCD_WIDTH; x++) {
            priv->fb[line][x] = priv->selected_palette
                                    [(pixels[x] & LCD_PALETTE_ALL) >> 4]
                                    [pixels[x] & 3];
        }
    }
}

void get_input(void) {
    static SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                exit(0);

            case SDL_CONTROLLERBUTTONDOWN:
            case SDL_CONTROLLERBUTTONUP:
                switch (event.cbutton.button) {
                    case SDL_CONTROLLER_BUTTON_A:
                        gb.direct.joypad_bits.a = !event.cbutton.state;
                        break;

                    case SDL_CONTROLLER_BUTTON_B:
                        gb.direct.joypad_bits.b = !event.cbutton.state;
                        break;

                    case SDL_CONTROLLER_BUTTON_BACK:
                        gb.direct.joypad_bits.select = !event.cbutton.state;
                        break;

                    case SDL_CONTROLLER_BUTTON_START:
                        gb.direct.joypad_bits.start = !event.cbutton.state;
                        break;

                    case SDL_CONTROLLER_BUTTON_DPAD_UP:
                        gb.direct.joypad_bits.up = !event.cbutton.state;
                        break;

                    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                        gb.direct.joypad_bits.right = !event.cbutton.state;
                        break;

                    case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                        gb.direct.joypad_bits.down = !event.cbutton.state;
                        break;

                    case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                        gb.direct.joypad_bits.left = !event.cbutton.state;
                        break;
                }

                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_RETURN:
                        gb.direct.joypad_bits.start = 0;
                        break;

                    case SDLK_BACKSPACE:
                        gb.direct.joypad_bits.select = 0;
                        break;

                    case SDLK_z:
                        gb.direct.joypad_bits.a = 0;
                        break;

                    case SDLK_x:
                        gb.direct.joypad_bits.b = 0;
                        break;

                    case SDLK_UP:
                        gb.direct.joypad_bits.up = 0;
                        break;

                    case SDLK_RIGHT:
                        gb.direct.joypad_bits.right = 0;
                        break;

                    case SDLK_DOWN:
                        gb.direct.joypad_bits.down = 0;
                        break;

                    case SDLK_LEFT:
                        gb.direct.joypad_bits.left = 0;
                        break;

                    case SDLK_r:
                        gb_reset();
                        break;
                }

                break;

            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_RETURN:
                        gb.direct.joypad_bits.start = 1;
                        break;

                    case SDLK_BACKSPACE:
                        gb.direct.joypad_bits.select = 1;
                        break;

                    case SDLK_z:
                        gb.direct.joypad_bits.a = 1;
                        break;

                    case SDLK_x:
                        gb.direct.joypad_bits.b = 1;
                        break;

                    case SDLK_UP:
                        gb.direct.joypad_bits.up = 1;
                        break;

                    case SDLK_RIGHT:
                        gb.direct.joypad_bits.right = 1;
                        break;

                    case SDLK_DOWN:
                        gb.direct.joypad_bits.down = 1;
                        break;

                    case SDLK_LEFT:
                        gb.direct.joypad_bits.left = 1;
                        break;
                }

                break;
        }
    }
}

void sdl_loop(void) {
    int delay;
    static unsigned int rtc_timer = 0;
    static uint_fast32_t new_ticks, old_ticks;
    const double target_speed_ms = 1000.0 / VERTICAL_SYNC;
    double speed_compensation = 0.0;

    /* Record save file every 60 seconds. */
    int save_timer = 60;
    /* Calculate the time taken to draw frame, then later add a
     * delay to cap at 60 fps. */
    old_ticks = SDL_GetTicks();

    /* Get joypad input. */
    get_input();
    /* Tick the internal RTC when 1 second has passed. */
    rtc_timer += target_speed_ms;

    if (rtc_timer >= 1000) {
        rtc_timer -= 1000;
        gb_tick_rtc();
    }

    /* Copy frame buffer to SDL screen. */
    SDL_UpdateTexture(texture, NULL, &priv.fb, LCD_WIDTH * sizeof(uint16_t));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    /* Use a delay that will draw the screen at a rate of 59.7275 Hz. */
    new_ticks = SDL_GetTicks();

    /* Since we can only delay for a maximum resolution of 1ms, we
     * can accumulate the error and compensate for the delay
     * accuracy when the delay compensation surpasses 1ms. */
    speed_compensation += target_speed_ms - (new_ticks - old_ticks);

    /* We cast the delay compensation value to an integer, since it
     * is the type used by SDL_Delay. This is where delay accuracy
     * is lost. */
    delay = (int)(speed_compensation);

    /* We then subtract the actual delay value by the requested
     * delay value. */
    speed_compensation -= delay;

    /* Only run delay logic if required. */
    if (delay > 0) {
        uint_fast32_t delay_ticks = SDL_GetTicks();
        uint_fast32_t after_delay_ticks;

        /* Tick the internal RTC when 1 second has passed. */
        rtc_timer += delay;

        if (rtc_timer >= 1000) {
            rtc_timer -= 1000;
            gb_tick_rtc();

            /* If 60 seconds has passed, record save file.
             * We do this because the external audio library
             * used contains asserts that will abort the
             * program without save.
             * TODO: Remove use of assert in audio library
             * in release build. */
            /* TODO: Remove all workarounds due to faulty
             * external libraries. */
            --save_timer;

            if (!save_timer) {
                write_cart_ram_file(save_file_name,
                                    &priv.cart_ram,
                                    gb_get_save_size());
                save_timer = 60;
            }
        }

        /* This will delay for at least the number of
         * milliseconds requested, so we have to compensate for
         * error here too. */
        SDL_Delay(delay);

        after_delay_ticks = SDL_GetTicks();
        speed_compensation += (double)delay -
                              (int)(after_delay_ticks - delay_ticks);
    }
}

void cleanup(void) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(texture);
    SDL_GameControllerClose(controller);
    SDL_Quit();
    /* Record save file. */
    write_cart_ram_file(save_file_name, &priv.cart_ram, gb_get_save_size());
    free(priv.rom);
    free(priv.cart_ram);
    /* If the save file name was automatically generated (which required memory
     * allocated on the help), then free it here. */
    free(save_file_name);
#ifndef _WIN32  //Crashes, not sure about other plats
    free(rom_file_name);
#endif
}

int main(int argc, char* argv[]) {
    (void)argc, (void)argv;
    atexit(cleanup);
    enum gb_init_error_e gb_ret;
    int ret = EXIT_SUCCESS;

#if defined(_WIN32)
    SDL_setenv("SDL_AUDIODRIVER", "directsound", SDL_TRUE);
#endif

    /* Initialise frontend implementation, in this case, SDL2. */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_AUDIO) < 0) {
        char buf[128];
        snprintf(buf, sizeof(buf),
                 "Unable to initialise SDL2: %s\n", SDL_GetError());
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", buf, NULL);
        ret = EXIT_FAILURE;
        goto out;
    }

    window = SDL_CreateWindow("suiCune",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              LCD_WIDTH * 2, LCD_HEIGHT * 2,
                              SDL_WINDOW_RESIZABLE | SDL_WINDOW_INPUT_FOCUS);

    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        ret = EXIT_FAILURE;
        goto out;
    }

    /* Copy input ROM file to allocated memory. */
    if ((priv.rom = read_rom_to_ram(rom_file_name)) == NULL) {
        printf("%d: %s\n", __LINE__, strerror(errno));
        ret = EXIT_FAILURE;
        goto out;
    }
    patch_rom(priv.rom);
    /* If no save file is specified, copy save file (with specific name) to
     * allocated memory. */
    if (save_file_name == NULL) {
        char *str_replace;
        const char extension[] = ".sav";

        /* Allocate enough space for the ROM file name, for the "sav"
         * extension and for the null terminator. */
        save_file_name = malloc(strlen(rom_file_name) + strlen(extension) + 1);

        if (save_file_name == NULL) {
            printf("%d: %s\n", __LINE__, strerror(errno));
            ret = EXIT_FAILURE;
            goto out;
        }

        /* Copy the ROM file name to allocated space. */
        strcpy(save_file_name, rom_file_name);

        /* If the file name does not have a dot, or the only dot is at
         * the start of the file name, set the pointer to begin
         * replacing the string to the end of the file name, otherwise
         * set it to the dot. */
        if ((str_replace = strrchr(save_file_name, '.')) == NULL ||
            str_replace == save_file_name)
            str_replace = save_file_name + strlen(save_file_name);

        /* Copy extension to string including terminating null byte. */
        for (unsigned int i = 0; i <= strlen(extension); i++)
            *(str_replace++) = extension[i];
    }

    /* TODO: Sanity check input GB file. */

    /* Initialise emulator context. */
    gb_ret = gb_init(&gb_rom_read, &gb_cart_ram_read, &gb_cart_ram_write,
                     &gb_error, &priv);

    switch (gb_ret) {
        case GB_INIT_NO_ERROR:
            break;

        case GB_INIT_CARTRIDGE_UNSUPPORTED:
            puts("Unsupported cartridge.");
            ret = EXIT_FAILURE;
            goto out;

        case GB_INIT_INVALID_CHECKSUM:
            puts("Invalid ROM: Checksum failure.");
            ret = EXIT_FAILURE;
            goto out;

        default:
            printf("Unknown error: %d\n", gb_ret);
            ret = EXIT_FAILURE;
            goto out;
    }

    /* Load Save File. */
    read_cart_ram_file(save_file_name, &priv.cart_ram, gb_get_save_size());

    /* Set the RTC of the game cartridge. Only used by games that support it. */
    {
        time_t rawtime;
        time(&rawtime);
#ifdef _POSIX_C_SOURCE
        struct tm timeinfo;
        localtime_r(&rawtime, &timeinfo);
#else
        struct tm *timeinfo;
        timeinfo = localtime(&rawtime);
#endif

        /* You could potentially force the game to allow the player to
         * reset the time by setting the RTC to invalid values.
         *
         * Using memset(&gb.cart_rtc, 0xFF, sizeof(gb.cart_rtc)) for
         * example causes Pokemon Gold/Silver to say "TIME NOT SET",
         * allowing the player to set the time without having some dumb
         * password.
         *
         * The memset has to be done directly to gb.cart_rtc because
         * gb_set_rtc() processes the input values, which may cause
         * games to not detect invalid values.
         */

        /* Set RTC. Only games that specify support for RTC will use
         * these values. */
#ifdef _POSIX_C_SOURCE
        gb_set_rtc(&timeinfo);
#else
        gb_set_rtc(timeinfo);
#endif
    }

    SDL_AudioDeviceID dev;

    {
        SDL_AudioSpec want, have;

        want.freq = AUDIO_SAMPLE_RATE;
        want.format = AUDIO_S16SYS,
        want.channels = 2;
        want.samples = AUDIO_SAMPLES;
        want.callback = audio_callback;
        want.userdata = NULL;

        printf("Audio device: %s\n", SDL_GetAudioDeviceName(0, 0));
        printf("Audio driver: %s\n", SDL_GetCurrentAudioDriver());

        if ((dev = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0)) == 0) {
            printf("SDL could not open audio device: %s\n", SDL_GetError());
            exit(EXIT_FAILURE);
        }

        audio_init();
        SDL_PauseAudioDevice(dev, 0);
    }
    gb_init_lcd(&lcd_draw_line);

    /* Allow the joystick input even if game is in background. */
    SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");

    if (SDL_GameControllerAddMappingsFromFile("gamecontrollerdb.txt") < 0) {
        /*printf("Unable to assign joystick mappings: %s\n",
               SDL_GetError());*/
    }

    /* Open the first available controller. */
    for (int i = 0; i < SDL_NumJoysticks(); i++) {
        if (!SDL_IsGameController(i))
            continue;

        controller = SDL_GameControllerOpen(i);

        if (controller) {
            printf("Game Controller %s connected.\n",
                   SDL_GameControllerName(controller));
            break;
        } else {
            printf("Could not open game controller %i: %s\n",
                   i, SDL_GetError());
        }
    }

    SDL_SetWindowMinimumSize(window, LCD_WIDTH, LCD_HEIGHT);

    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        printf("Could not create renderer: %s\n", SDL_GetError());
        ret = EXIT_FAILURE;
        goto out;
    }

    if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255) < 0) {
        printf("Renderer could not draw color: %s\n", SDL_GetError());
        ret = EXIT_FAILURE;
        goto out;
    }

    if (SDL_RenderClear(renderer) < 0) {
        printf("Renderer could not clear: %s\n", SDL_GetError());
        ret = EXIT_FAILURE;
        goto out;
    }

    SDL_RenderPresent(renderer);

    /* Use integer scale. */
    SDL_RenderSetLogicalSize(renderer, LCD_WIDTH, LCD_HEIGHT);
    SDL_RenderSetIntegerScale(renderer, 1);

    texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_RGB555,
                                SDL_TEXTUREACCESS_STREAMING,
                                LCD_WIDTH, LCD_HEIGHT);

    if (texture == NULL) {
        printf("Texture could not be created: %s\n", SDL_GetError());
        ret = EXIT_FAILURE;
        goto out;
    }

    while (SDL_QuitRequested() == SDL_FALSE) {
        /* Execute CPU cycles until the screen has to be redrawn. */
        gb_run_frame();
    }

quit:
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(texture);
    SDL_GameControllerClose(controller);
    SDL_Quit();

    /* Record save file. */
    write_cart_ram_file(save_file_name, &priv.cart_ram, gb_get_save_size());

out:
    free(priv.rom);
    free(priv.cart_ram);

    /* If the save file name was automatically generated (which required memory
     * allocated on the help), then free it here. */
    free(save_file_name);

#ifndef _WIN32  //Crashes
    free(rom_file_name);
#endif

    return ret;
}
