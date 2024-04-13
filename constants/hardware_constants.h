// Graciously derived from:
// https://gbdev.io/pandocs/
// https://github.com/gbdev/hardware.inc
// http://gameboy.mongenel.com/dmg/asmmemmap.html

// memory map
#define VRAM_Begin 0x8000
#define VRAM_End 0xa000
#define SRAM_Begin 0xa000
#define SRAM_End 0xc000
#define WRAM0_Begin 0xc000
#define WRAM0_End 0xd000
#define WRAM1_Begin 0xd000
#define WRAM1_End 0xe000
// hardware registers 0xff00-0xff80 (see below)
#define HRAM_Begin 0xff80
#define HRAM_End 0xffff

// MBC3
#define MBC3SRamEnable 0x0000
#define MBC3RomBank 0x2000
#define MBC3SRamBank 0x4000
#define MBC3LatchClock 0x6000
#define MBC3RTC 0xa000

#define SRAM_DISABLE 0x00
#define SRAM_ENABLE 0x0a

#define NUM_SRAM_BANKS 8

#define RTC_S 0x08   // Seconds   0-59 (0-3Bh)
#define RTC_M 0x09   // Minutes   0-59 (0-3Bh)
#define RTC_H 0x0a   // Hours     0-23 (0-17h)
#define RTC_DL 0x0b  // Lower 8 bits of Day Counter (0-FFh)
#define RTC_DH 0x0c  // Upper 1 bit of Day Counter, Carry Bit, Halt Flag
                     // Bit 0  Most significant bit of Day Counter (Bit 8)
                     // Bit 6  Halt (0=Active, 1=Stop Timer)
                     // Bit 7  Day Counter Carry Bit (1=Counter Overflow)

// interrupt flags
#define VBLANK 0
#define LCD_STAT 1
#define TIMER 2
#define SERIAL 3
#define JOYPAD 4
#define IE_DEFAULT ((1 << SERIAL) | (1 << TIMER) | (1 << LCD_STAT) | (1 << VBLANK))

// OAM attribute flags
#define OAM_TILE_BANK 3
#define OAM_OBP_NUM 4  // non CGB Mode Only
#define OAM_X_FLIP 5
#define OAM_Y_FLIP 6
#define OAM_PRIORITY 7  // 0: OBJ above BG, 1: OBJ behind BG (colors 1-3)

// BG Map attribute flags
#define PALETTE_MASK 0b111
#define VRAM_BANK_1 (1 << OAM_TILE_BANK)  // 0x08
#define OBP_NUM (1 << OAM_OBP_NUM)        // 0x10
#define X_FLIP (1 << OAM_X_FLIP)          // 0x20
#define Y_FLIP (1 << OAM_Y_FLIP)          // 0x40
#define PRIORITY (1 << OAM_PRIORITY)      // 0x80

// Hardware registers
#define rJOYP 0xff00  // Joypad (R/W)
#define rSB 0xff01    // Serial transfer data (R/W)
#define rSC 0xff02    // Serial Transfer Control (R/W)
#define rSC_ON 7
#define rSC_CGB 1
#define rSC_CLOCK 0
#define rDIV 0xff04   // Divider Register (R/W)
#define rTIMA 0xff05  // Timer counter (R/W)
#define rTMA 0xff06   // Timer Modulo (R/W)
#define rTAC 0xff07   // Timer Control (R/W)
#define rTAC_ON 2
#define rTAC_4096_HZ 0b00
#define rTAC_262144_HZ 0b01
#define rTAC_65536_HZ 0b10
#define rTAC_16384_HZ 0b11
#define rIF 0xff0f    // Interrupt Flag (R/W)
#define rNR10 0xff10  // Channel 1 Sweep register (R/W)
#define rNR11 0xff11  // Channel 1 Sound length/Wave pattern duty (R/W)
#define rNR12 0xff12  // Channel 1 Volume Envelope (R/W)
#define rNR13 0xff13  // Channel 1 Frequency lo (Write Only)
#define rNR14 0xff14  // Channel 1 Frequency hi (R/W)
#define rNR20 0xff15  // Channel 2 Sweep register (R/W)
#define rNR21 0xff16  // Channel 2 Sound Length/Wave Pattern Duty (R/W)
#define rNR22 0xff17  // Channel 2 Volume Envelope (R/W)
#define rNR23 0xff18  // Channel 2 Frequency lo data (W)
#define rNR24 0xff19  // Channel 2 Frequency hi data (R/W)
#define rNR30 0xff1a  // Channel 3 Sound on/off (R/W)
#define rNR31 0xff1b  // Channel 3 Sound Length
#define rNR32 0xff1c  // Channel 3 Select output level (R/W)
#define rNR33 0xff1d  // Channel 3 Frequency's lower data (W)
#define rNR34 0xff1e  // Channel 3 Frequency's higher data (R/W)
#define rNR40 0xff1f  // Channel 4 Sweep register (R/W)
#define rNR41 0xff20  // Channel 4 Sound Length (R/W)
#define rNR42 0xff21  // Channel 4 Volume Envelope (R/W)
#define rNR43 0xff22  // Channel 4 Polynomial Counter (R/W)
#define rNR44 0xff23  // Channel 4 Counter/consecutive// Inital (R/W)
#define rNR50 0xff24  // Channel control / ON-OFF / Volume (R/W)
#define rNR51 0xff25  // Selection of Sound output terminal (R/W)
#define rNR52 0xff26  // Sound on/off
#define rWave_0 0xff30
#define rWave_1 0xff31
#define rWave_2 0xff32
#define rWave_3 0xff33
#define rWave_4 0xff34
#define rWave_5 0xff35
#define rWave_6 0xff36
#define rWave_7 0xff37
#define rWave_8 0xff38
#define rWave_9 0xff39
#define rWave_a 0xff3a
#define rWave_b 0xff3b
#define rWave_c 0xff3c
#define rWave_d 0xff3d
#define rWave_e 0xff3e
#define rWave_f 0xff3f
#define rLCDC 0xff40            // LCD Control (R/W)
#define rLCDC_BG_PRIORITY 0     // 0=Off, 1=On
#define rLCDC_SPRITES_ENABLE 1  // 0=Off, 1=On
#define rLCDC_SPRITE_SIZE 2     // 0=8x8, 1=8x16
#define rLCDC_BG_TILEMAP 3      // 0=9800-9BFF, 1=9C00-9FFF
#define rLCDC_TILE_DATA 4       // 0=8800-97FF, 1=8000-8FFF
#define rLCDC_WINDOW_ENABLE 5   // 0=Off, 1=On
#define rLCDC_WINDOW_TILEMAP 6  // 0=9800-9BFF, 1=9C00-9FFF
#define rLCDC_ENABLE 7          // 0=Off, 1=On
#define LCDC_DEFAULT ((1 << rLCDC_ENABLE) | (1 << rLCDC_WINDOW_TILEMAP) | (1 << rLCDC_WINDOW_ENABLE) | (1 << rLCDC_SPRITES_ENABLE) | (1 << rLCDC_BG_PRIORITY))
#define rSTAT 0xff41  // LCDC Status (R/W)
#define rSCY 0xff42   // Scroll Y (R/W)
#define rSCX 0xff43   // Scroll X (R/W)
#define rLY 0xff44    // LCDC Y-Coordinate (R)
#define LY_VBLANK 144
#define rLYC 0xff45   // LY Compare (R/W)
#define rDMA 0xff46   // DMA Transfer and Start Address (W)
#define rBGP 0xff47   // BG Palette Data (R/W) - Non CGB Mode Only
#define rOBP0 0xff48  // Object Palette 0 Data (R/W) - Non CGB Mode Only
#define rOBP1 0xff49  // Object Palette 1 Data (R/W) - Non CGB Mode Only
#define rWY 0xff4a    // Window Y Position (R/W)
#define rWX 0xff4b    // Window X Position minus 7 (R/W)
#define rLCDMODE 0xff4c
#define rKEY1 0xff4d  // CGB Mode Only - Prepare Speed Switch
#define rVBK 0xff4f   // CGB Mode Only - VRAM Bank
#define rBLCK 0xff50
#define rHDMA1 0xff51  // CGB Mode Only - New DMA Source, High
#define rHDMA2 0xff52  // CGB Mode Only - New DMA Source, Low
#define rHDMA3 0xff53  // CGB Mode Only - New DMA Destination, High
#define rHDMA4 0xff54  // CGB Mode Only - New DMA Destination, Low
#define rHDMA5 0xff55  // CGB Mode Only - New DMA Length/Mode/Start
#define rRP 0xff56     // CGB Mode Only - Infrared Communications Port
#define rRP_LED_ON 0
#define rRP_RECEIVING 1
#define rRP_ENABLE_READ_MASK 0b11000000
#define rBGPI 0xff68            // CGB Mode Only - Background Palette Index
#define rBGPI_AUTO_INCREMENT 7  // increment rBGPI after write to rBGPD
#define rBGPD 0xff69            // CGB Mode Only - Background Palette Data
#define rOBPI 0xff6a            // CGB Mode Only - Sprite Palette Index
#define rOBPI_AUTO_INCREMENT 7  // increment rOBPI after write to rOBPD
#define rOBPD 0xff6b            // CGB Mode Only - Sprite Palette Data
#define rUNKNOWN1 0xff6c        // (FEh) Bit 0 (Read/Write) - CGB Mode Only
#define rSVBK 0xff70            // CGB Mode Only - WRAM Bank
#define rUNKNOWN2 0xff72        // (00h) - Bit 0-7 (Read/Write)
#define rUNKNOWN3 0xff73        // (00h) - Bit 0-7 (Read/Write)
#define rUNKNOWN4 0xff74        // (00h) - Bit 0-7 (Read/Write) - CGB Mode Only
#define rUNKNOWN5 0xff75        // (8Fh) - Bit 4-6 (Read/Write)
#define rUNKNOWN6 0xff76        // (00h) - Always 00h (Read Only)
#define rUNKNOWN7 0xff77        // (00h) - Always 00h (Read Only)
#define rIE 0xffff              // Interrupt Enable (R/W)
