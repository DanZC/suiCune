#pragma once

enum {
    AUDIO_BANK_SFX,
    AUDIO_BANK_SFX_CRYSTAL,
    AUDIO_BANK_CRY,
    AUDIO_BANK_MUSIC_1,
    AUDIO_BANK_MUSIC_2,
    AUDIO_BANK_MUSIC_3,
    AUDIO_BANK_MUSIC_4,
    NUM_AUDIO_BANKS,
};

void LoadAudioData(void);
uint8_t GetAudioDataByte(uint8_t bank, uint16_t offset);
