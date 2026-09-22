#include "../tools/emu/minigb_apu/minigb_apu.h"

void apu_init(void) {
    audio_init();
}

uint8_t apu_read(uint16_t addr) {
    return audio_read(addr);
}

void apu_write(uint16_t addr, uint8_t val) {
    audio_write(addr, val);
}

void apu_write16(uint16_t addr, uint16_t val) {
    audio_write(addr, val & 0xff);
    audio_write(addr + 1, val >> 8);
}

void apu_callback(void *ptr, uint8_t *data, int len) {
    audio_callback(ptr, data, len);
}

