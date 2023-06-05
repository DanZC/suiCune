#pragma pack(1)
struct Channel {
    uint16_t musicId;
    uint8_t musicBank;

    union {
        struct {
            uint8_t channelOn : 1;
            uint8_t subroutine : 1;
            uint8_t looping : 1;
            uint8_t sfx : 1;
            uint8_t noise : 1;
            uint8_t cry : 1;
            uint8_t unused1 : 2;

            uint8_t vibrato : 1;
            uint8_t pitchSlide : 1;
            uint8_t dutyLoop : 1;
            uint8_t unused2 : 1;
            uint8_t pitchOffsetEnabled : 1;
            uint8_t unkn0D : 1;  // unused
            uint8_t unkn0E : 1;  // unused
            uint8_t unkn0F : 1;

            uint8_t vibratoDir : 1;
            uint8_t pitchSlideDir : 1;
            uint8_t unused3 : 6;
        };
        uint8_t flags[3];
    };

    uint16_t musicAddress;
    uint16_t lastMusicAddress;
    uint16_t unused;

    union {
        struct {
            uint8_t dutyOverride : 1;
            uint8_t freqOverride : 1;
            uint8_t unused4 : 1;
            uint8_t pitchSweep : 1;
            uint8_t noiseSampling : 1;
            uint8_t rest : 1;
            uint8_t vibratoOverride : 1;
            uint8_t unused5 : 1;
        };
        uint8_t noteFlags;
    };

    uint8_t condition;
    uint8_t dutyCycle;
    uint8_t volumeEnvelope;
    uint16_t frequency;
    uint8_t pitch;
    uint8_t octave;
    uint8_t transposition;
    uint8_t noteDuration;
    uint16_t field16;  // noteDurationFraction

    uint8_t loopCount;
    uint16_t tempo;
    uint8_t tracks;
    uint8_t dutyCyclePattern;
    uint8_t vibratoDelayCount;
    uint8_t vibratoDelay;
    uint8_t vibratoExtent;
    uint8_t vibratoRate;
    uint16_t pitchSlideTarget;
    uint8_t pitchSlideAmount;
    uint8_t pitchSlideAmountFraction;
    uint16_t field25;

    uint16_t pitchOffset;
    uint8_t field29;   // unused
    uint16_t field2a;  // unused
    uint8_t field2c;   // unused
    uint8_t noteLength;
    uint8_t field2e;
    uint8_t field2f;
    uint16_t field30;
};

void v_InitSound(void);
void MusicFadeRestart(void);
void MusicOn(void);
void MusicOff(void);
void v_UpdateSound(void);
void UpdateChannels(void);
void UpdateChannels_Channel1_LowHealth(void);
void UpdateChannels_Channel1(void);
void UpdateChannels_Channel2(void);
void UpdateChannels_Channel3(void);
void UpdateChannels_load_wave_pattern(uint8_t);
void UpdateChannels_Channel4(void);
int v_CheckSFX(void);
void PlayDanger(void);
void FadeMusic(void);
void LoadNote(void);
void HandleTrackVibrato(void);
void ApplyPitchSlide(void);
void ApplyPitchSlide_finished_pitch_slide(void);
void ApplyPitchSlide_continue_pitch_slide(void);
void HandleNoise(void);
void ReadNoiseSample(void);
void ParseMusic(void);
void RestoreVolume(void);
void ParseSFXOrCry(void);
void GetNoiseSample(void);
void ParseMusicCommand(void);
void MusicCommands(void);
void MusicNone(void);
void Music_Ret(void);
void Music_Call(void);
void Music_Jump(void);
void Music_Loop(void);
void Music_SetCondition(void);
void Music_JumpIf(void);
void MusicEE(void);
void MusicE2(void);
void Music_Vibrato(void);
void Music_PitchSlide(void);
void Music_PitchOffset(void);
void MusicE7(void);
void Music_DutyCyclePattern(void);
void MusicE8(void);
void Music_ToggleSFX(void);
void Music_ToggleNoise(void);
void Music_SFXToggleNoise(void);
void Music_NoteType(void);
void Music_PitchSweep(void);
void Music_DutyCycle(void);
void Music_VolumeEnvelope(void);
void Music_Tempo(void);
void Music_Octave(void);
void Music_Transpose(void);
void Music_StereoPanning(void);
void Music_ForceStereoPanning(void);
void Music_Volume(void);
void Music_TempoRelative(void);
void Music_SFXPriorityOn(void);
void Music_SFXPriorityOff(void);
void Music_RestartChannel(void);
void Music_NewSong(void);
uint8_t GetMusicByte(void);
uint16_t GetFrequency(uint8_t, uint8_t);
void SetNoteDuration(uint8_t);
void SetNoteDuration_Multiply(void);
void SetGlobalTempo(uint16_t);
void Tempo(void);
void StartChannel(void);
void SetLRTracks(void);
void v_PlayMusic(uint16_t);
void v_PlayCry(void);
void v_PlaySFX(void);
void PlayStereoSFX(void);
uint16_t LoadChannel(uint16_t);
void ChannelInit(uint8_t);
uint8_t LoadMusicByte(uint16_t);
void GetLRTracks(void);
void MonoTracks(void);
void StereoTracks(void);
void ChannelPointers(void);
void ClearChannels(void);
void ClearChannel(uint16_t);
void PlayTrainerEncounterMusic(void);
//#include "audio/notes.h"
//#include "audio/wave_samples.h"
//#include "audio/drumkits.h"
