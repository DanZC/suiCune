#include "../constants.h"
#include "load.h"
#include "sfx.h"
#include "sfx_crystal.h"
#include "cries.h"
#include <assert.h>

asset_s SoundDataBuffers[NUM_AUDIO_BANKS] = {0};

static const char* SoundDataPaths[] = {
    [AUDIO_BANK_SFX]            = "audio/sfx.bin",
    [AUDIO_BANK_SFX_CRYSTAL]    = "audio/sfx_crystal.bin",
    [AUDIO_BANK_CRY]            = "audio/cries.bin",
    [AUDIO_BANK_MUSIC_1]        = "audio/music_1.bin",
    [AUDIO_BANK_MUSIC_2]        = "audio/music_2.bin",
    [AUDIO_BANK_MUSIC_3]        = "audio/music_3.bin",
    [AUDIO_BANK_MUSIC_4]        = "audio/music_4.bin",
};
static_assert(lengthof(SoundDataPaths) == NUM_AUDIO_BANKS, "");

void LoadAudioData(void) {
    for(uint32_t i = 0; i < lengthof(SoundDataPaths); ++i) {
        if(SoundDataBuffers[i].ptr)
            FreeAsset(SoundDataBuffers[i]);
        SoundDataBuffers[i] = LoadAsset(SoundDataPaths[i]);
    }
}

uint8_t GetAudioDataByte(uint8_t bank, uint16_t offset) {
    assert(bank < NUM_AUDIO_BANKS && "Bad bank");
    assert(SoundDataBuffers[bank].ptr != NULL && "data buffer not loaded");
    assert(offset < SoundDataBuffers[bank].size && "out of bounds");
    uint8_t* ptr = SoundDataBuffers[bank].ptr;
    return ptr[offset];
}
