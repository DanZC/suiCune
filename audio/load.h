#pragma once

enum {
    AUDIO_BANK_SFX,
    AUDIO_BANK_SFX_CRYSTAL,
    AUDIO_BANK_CRY,
    NUM_AUDIO_BANKS,
};

void LoadAudioData(void);
uint8_t GetAudioDataByte(uint8_t bank, uint16_t offset);
