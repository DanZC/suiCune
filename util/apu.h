#pragma once

void apu_init(void);
uint8_t apu_read(uint16_t addr);
void apu_write(uint16_t addr, uint8_t val);
void apu_write16(uint16_t addr, uint16_t val);
void apu_callback(void *ptr, uint8_t *data, int len);
