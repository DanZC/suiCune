#include "../constants.h"

#include "engine.h"
#include "drumkits.h"
#include "notes.h"
#include "wave_samples.h"

//  The entire sound engine. Uses section "audio" in WRAM.

//  Interfaces are in bank 0.

//  Notable functions:
//      FadeMusic
//      PlayStereoSFX

struct Channel *chan[8];
struct Channel *curChan;
int curChannel;
uint16_t channelPointers[8] = {wChannel1,
                               wChannel2,
                               wChannel3,
                               wChannel4,
                               wChannel5,
                               wChannel6,
                               wChannel7,
                               wChannel8};

uint8_t *noiseSampleAddress;
uint8_t channelJumpCondition[4];

void v_InitSound(void) {  //  restart sound operation, clear all relevant hardware registers & wram
    for (int i = 0; i < NUM_CHANNELS; i++)
        chan[i] = gb_pointer(channelPointers[i]);
    MusicOff();
    ClearChannels();
    for (int i = wAudio; i < wAudioEnd; i++)
        gb_write(i, 0);
    gb_write(wVolume, MAX_VOLUME);
    MusicOn();
}

void MusicFadeRestart(void) {  //  restart but keep the music id to fade in to
    uint16_t musicId = gb_read16(wMusicFadeID);
    v_InitSound();
    gb_write16(wMusicFadeID, musicId);
}

void MusicOn(void) {
    gb_write(wMusicPlaying, 1);
}

void MusicOff(void) {
    gb_write(wMusicPlaying, 0);
}

void v_UpdateSound(void) {  // called once per frame
    if (!gb_read(wMusicPlaying))
        return;  // no use updating audio if it's not playing
    gb_write(wSoundOutput, 0);
    for (curChannel = 0; curChannel < NUM_CHANNELS; curChannel++) {
        gb_write(wCurChannel, curChannel);
        curChan = chan[curChannel];
        if (curChan->channelOn) {                                    // is the channel active?
            if (curChan->noteDuration < 2) {                         // check time left in the current note
                curChan->vibratoDelayCount = curChan->vibratoDelay;  // reset vibrato delay
                curChan->pitchSlide = 0;                             // turn vibrato off for now
                ParseMusic();                                        // get next note
            } else
                curChan->noteDuration--;
            ApplyPitchSlide();
            gb_write(wCurTrackDuty, curChan->dutyCycle);                 // duty cycle
            gb_write(wCurTrackVolumeEnvelope, curChan->volumeEnvelope);  // volume envelope
            gb_write16(wCurTrackFrequency, curChan->frequency);          // frequency
            HandleTrackVibrato();                                        // handle vibrato and other things
            HandleNoise();
            if ((gb_read(wSFXPriority))                                 // turn off music when playing sfx?
                && (curChannel < NUM_MUSIC_CHANS)) {                    // are we in a sfx channel right now?
                for (int i = NUM_MUSIC_CHANS; i < NUM_CHANNELS; i++) {  // are any sfx channels active?
                    if (chan[i]->channelOn) {                           // if so, mute
                        curChan->rest = 1;
                        break;
                    }
                }
            }
            if ((curChannel >= NUM_MUSIC_CHANS) || (!chan[curChannel + NUM_MUSIC_CHANS]->channelOn)) {  // are we in a sfx channel right now?
                UpdateChannels();
                gb_write(wSoundOutput, gb_read(wSoundOutput) | curChan->tracks);
            }
            curChan->noteFlags = 0;  // clear note flags
        }
    }
    PlayDanger();
    FadeMusic();                             // fade music in/out
    gb_write(rNR50, gb_read(wVolume));       // write volume to hardware register
    gb_write(rNR51, gb_read(wSoundOutput));  // write SO on/off to hardware register
}

void UpdateChannels(void) {
    static void (*ChannelFunctions[8])(void) = {UpdateChannels_Channel1_LowHealth,
                                                UpdateChannels_Channel2,
                                                UpdateChannels_Channel3,
                                                UpdateChannels_Channel4,
                                                UpdateChannels_Channel1,
                                                UpdateChannels_Channel2,
                                                UpdateChannels_Channel3,
                                                UpdateChannels_Channel4};
    return ChannelFunctions[curChannel]();
}

void UpdateChannels_Channel1_LowHealth(void) {
    if (!(gb_read(wLowHealthAlarm) & (1 << DANGER_ON_F)))
        UpdateChannels_Channel1();
}

void UpdateChannels_Channel1(void) {
    if (curChan->pitchSweep)
        gb_write(rNR10, gb_read(wPitchSweep));
    if (curChan->rest) {
        gb_write(rNR52, gb_read(rNR52) & 0b10001110);
        ClearChannel(rNR10);
    } else if (curChan->noiseSampling) {
        gb_write(rNR11, (gb_read(rNR11) & 0x3F) | gb_read(wCurTrackDuty));
        gb_write(rNR12, gb_read(wCurTrackVolumeEnvelope));
        gb_write16(rNR13, gb_read16(wCurTrackFrequency) | 0x8000);
    } else if (curChan->freqOverride) {
        gb_write16(rNR13, gb_read16(wCurTrackFrequency));
        if (curChan->dutyOverride)
            gb_write(rNR11, (gb_read(rNR11) & 0x3F) | gb_read(wCurTrackDuty));
    } else if (curChan->vibratoOverride) {
        gb_write(rNR11, (gb_read(rNR11) & 0x3F) | gb_read(wCurTrackDuty));
        gb_write(rNR13, gb_read(wCurTrackFrequency));
    } else if (curChan->dutyOverride)
        gb_write(rNR11, (gb_read(rNR11) & 0x3F) | gb_read(wCurTrackDuty));
}

void UpdateChannels_Channel2(void) {
    if (curChan->rest) {
        gb_write(rNR52, gb_read(rNR52) & 0b10001101);
        ClearChannel(rNR20);
    } else if (curChan->noiseSampling) {
        gb_write(rNR21, (gb_read(rNR21) & 0x3F) | gb_read(wCurTrackDuty));
        gb_write(rNR22, gb_read(wCurTrackVolumeEnvelope));
        gb_write16(rNR23, gb_read16(wCurTrackFrequency) | 0x8000);
    } else if (curChan->freqOverride) {
        gb_write16(rNR23, gb_read16(wCurTrackFrequency));
    } else if (curChan->vibratoOverride) {
        gb_write(rNR21, (gb_read(rNR21) & 0x3F) | gb_read(wCurTrackDuty));
        gb_write(rNR23, gb_read(wCurTrackFrequency));
    } else if (curChan->dutyOverride)
        gb_write(rNR21, (gb_read(rNR21) & 0x3F) | gb_read(wCurTrackDuty));
}

void UpdateChannels_Channel3(void) {
    if (curChan->rest) {
        gb_write(rNR52, gb_read(rNR52) & 0b10001011);
        ClearChannel(rNR30);
    } else if (curChan->noiseSampling) {
        gb_write(rNR31, 0x3F);
        UpdateChannels_load_wave_pattern(gb_read(wCurTrackVolumeEnvelope) & 0xF);
        gb_write16(rNR33, gb_read16(wCurTrackFrequency) | 0x8000);
    } else if (curChan->vibratoOverride) {
        gb_write(rNR33, gb_read(wCurTrackFrequency));
    }
}

void UpdateChannels_load_wave_pattern(uint8_t sampleId) {
    int samplePointer = sampleId << 5;
    gb_write(rNR30, 0);
    for (int i = 0; i < 16; i++, samplePointer += 2)
        gb_write(rWave_0 + i, (WaveSamples[samplePointer] << 4) | WaveSamples[samplePointer + 1]);
    gb_write(rNR32, (gb_read(wCurTrackVolumeEnvelope) & 0x30) << 1);
    gb_write(rNR30, 0x80);
}

void UpdateChannels_Channel4(void) {
    if (curChan->rest) {
        gb_write(rNR52, gb_read(rNR52) & 0b10000111);
        ClearChannel(rNR40);
    } else if (curChan->noiseSampling) {
        gb_write(rNR41, 0x3F);
        gb_write(rNR42, gb_read(wCurTrackVolumeEnvelope));
        gb_write(rNR43, gb_read(wCurTrackFrequency));
        gb_write(rNR44, 0x80);
    }
}

int v_CheckSFX(void) {                                      // check if any sfx channels are active
    for (int i = NUM_MUSIC_CHANS; i < NUM_CHANNELS; i++) {  // are any sfx channels active?
        if (chan[i]->channelOn)
            return 1;
    }
    return 0;
}

void PlayDanger(void) {
    if ((gb_read(wLowHealthAlarm) & (1 << DANGER_ON_F))) {
        uint8_t lowHealthTimer = gb_read(wLowHealthAlarm) ^ (1 << DANGER_ON_F);
        uint16_t lowHealthPitch;
        if (!v_CheckSFX()) {                 // Don't do anything if SFX is being played
            if (!(lowHealthTimer & 0x0F)) {  // switch pitch
                if (!lowHealthTimer) {       // Play the high tone (timer = 0)
                    lowHealthPitch = 0x750;
                } else {  // Play the low tone (timer = 16)
                    lowHealthPitch = 0x6EE;
                }
                gb_write(rNR10, 0);
                gb_write(rNR11, 0x80);  // duty 50%
                gb_write(rNR12, 0xE2);  // volume 14, envelope decrease sweep 2
                gb_write16(rNR13, lowHealthPitch | 0x8000);
            }
        }
        if (++lowHealthTimer == 30)
            lowHealthTimer = 0;
        gb_write(wLowHealthAlarm, lowHealthTimer | (1 << DANGER_ON_F));  // Make sure the danger sound is kept on
        gb_write(wSoundOutput, gb_read(wSoundOutput) | 0x11);            // Enable channel 1 if it's off
    }
}

void FadeMusic(void) {
    //  fade music if applicable
    //  usage:
    //     write to wMusicFade
    //     song fades out at the given rate
    //     load song id in wMusicFadeID
    //     fade new song in
    //  notes:
    //     max # frames per volume level is $3f
    if (gb_read(wMusicFade)) {           // fading?
        if (gb_read(wMusicFadeCount)) {  // has the count ended?
            gb_write(wMusicFadeCount, gb_read(wMusicFadeCount) - 1);
        } else {
            gb_write(wMusicFadeCount, gb_read(wMusicFade) & 0x3F);  // get new count
            uint8_t curVol = gb_read(wVolume) & VOLUME_SO1_LEVEL;   // get SO1 volume
            if (gb_read(wMusicFade) & (1 << MUSIC_FADE_IN_F)) {     // fading in?
                if (gb_read(wVolume) & (MAX_VOLUME & 0xF)) {        // are we done?
                    gb_write(wMusicFade, 0);                        // we're done
                    return;
                }
                curVol++;  // inc volume
            } else {       // fading out
                if (!(gb_read(wVolume) & VOLUME_SO1_LEVEL)) {
                    gb_write(wVolume, 0);                        // make sure volume is off
                    if (gb_read(wPlayerState) == PLAYER_BIKE) {  // did we just get on a bike?
                        MusicFadeRestart();                      // restart sound
                        gb_write(wVolume, 0);
                        v_PlayMusic(gb_read16(wMusicFadeID));                                // load new song
                        gb_write(wMusicFade, gb_read(wMusicFade) | (1 << MUSIC_FADE_IN_F));  // fade in
                        return;
                    }
                    MusicFadeRestart();  // restart sound
                    if (gb_read(wMusicFadeID)) {
                        v_PlayMusic(gb_read16(wMusicFadeID));  // load new song
                    }
                    gb_write(wMusicFade, 0);  // stop fading
                    return;
                }
                curVol--;  // dec volume
            }
            curVol |= curVol << 4;  // hi = lo
            gb_write(wVolume, curVol);
        }
    }
}

void LoadNote(void) {
    if (curChan->pitchSlide) {                                                     // wait for pitch slide to finish
        int16_t noteDuration = curChan->noteDuration - gb_read(wCurNoteDuration);  // get note duration
        if (noteDuration < 0)
            noteDuration = 1;  // Oversight? This could allow a division by 0
        gb_write(wCurNoteDuration, noteDuration);
        uint16_t freqDiff;
        if (curChan->frequency > curChan->pitchSlideTarget) {  // get direction of pitch slide
            curChan->pitchSlideDir = 0;
            freqDiff = curChan->frequency - curChan->pitchSlideTarget;
        } else {
            curChan->pitchSlideDir = 1;
            freqDiff = curChan->pitchSlideTarget - curChan->frequency;
        }
        curChan->pitchSlideAmount = freqDiff / noteDuration;
        curChan->pitchSlideAmountFraction = freqDiff % noteDuration;
        curChan->field25 = 0;
    }
}

void HandleTrackVibrato(void) {  // handle duty, cry pitch, and vibrato
    uint16_t freq;
    if (curChan->dutyLoop) {  // duty cycle looping
        curChan->dutyCyclePattern = (curChan->dutyCyclePattern << 2) | (curChan->dutyCyclePattern >> 6);
        gb_write(wCurTrackDuty, (curChan->dutyCyclePattern & 0xC0));
        curChan->dutyOverride = 1;
    }
    if (curChan->pitchOffsetEnabled) {
        freq = gb_read16(wCurTrackFrequency);
        gb_write16(wCurTrackFrequency, freq + curChan->pitchOffset);
    }
    if (curChan->vibrato) {                // is vibrato on?
        if (curChan->vibratoDelayCount) {  // is vibrato active for this note yet?
            curChan->vibratoDelayCount--;
            return;
        }
        if (!curChan->vibratoExtent)
            return;                        // is the extent nonzero?
        if (curChan->vibratoRate & 0xF) {  // is it time to toggle vibrato up/down?
            curChan->vibratoRate--;
            return;
        }
        curChan->vibratoRate |= curChan->vibratoRate >> 4;  // refresh count
        uint8_t vibExt = curChan->vibratoExtent;
        freq = gb_read16(wCurTrackFrequency) & 0xFF;  // Only the lower 8-bits are needed (which seems odd)
        curChan->vibratoDir ^= 1;
        if (curChan->vibratoDir) {  // toggle vibrato up/down
            vibExt &= 0xF0;
            vibExt = vibExt >> 4;
            if (vibExt + freq > 0xFF)
                freq = 0xFF;
            else
                freq += vibExt;
        } else {
            vibExt &= 0xF;
            if (vibExt > freq)
                freq = 0;
            else
                freq -= vibExt;
        }
        freq |= gb_read16(wCurTrackFrequency) & 0xFF00;  // get the upper byte back (since the math dealt with the lower byte)
        gb_write16(wCurTrackFrequency, freq);
        curChan->vibratoOverride = 1;
    }
}

void ApplyPitchSlide(void) {
    if (curChan->pitchSlide) {  // quit if pitch slide inactive
        uint16_t freq = curChan->frequency;
        if (curChan->pitchSlideDir) {  // check whether pitch slide is going up or down
            freq += curChan->pitchSlideAmount;
            if (curChan->field25 + curChan->pitchSlideAmountFraction >= 0x100)
                freq++;
            curChan->field25 += curChan->pitchSlideAmountFraction;
            if (freq > curChan->pitchSlideTarget) {  // are we done?
                curChan->pitchSlide = 0;
                curChan->pitchSlideDir = 0;
            } else {
                curChan->frequency = freq;
                curChan->freqOverride = 1;
                curChan->dutyOverride = 1;
            }
        } else {
            freq -= curChan->pitchSlideAmount;
            if (curChan->field25 + curChan->field25 >= 0x100)
                freq--;
            curChan->field25 += curChan->field25;
            if (freq < curChan->pitchSlideTarget) {  // are we done?
                curChan->pitchSlide = 0;
                curChan->pitchSlideDir = 0;
            } else {
                curChan->frequency = freq;
                curChan->freqOverride = 1;
                curChan->dutyOverride = 1;
            }
        }
    }
}

void HandleNoise(void) {
    if (curChan->noise) {  // is noise sampling on?
        if ((gb_read(wCurChannel) & (1 << NOISE_CHAN_F)) || (!chan[CHAN8]->channelOn) || (!chan[CHAN8]->noise)) {
            if (!gb_read(wNoiseSampleDelay))
                ReadNoiseSample();
            else
                gb_write(wNoiseSampleDelay, gb_read(wNoiseSampleDelay) - 1);
        }
    }
}

void ReadNoiseSample(void) {  // samples in drumkits.h
    if (noiseSampleAddress) {
        if (*(noiseSampleAddress) != sound_ret_cmd) {
            gb_write(wNoiseSampleDelay, (*(noiseSampleAddress++) & 0xF) + 1);
            gb_write(wCurTrackVolumeEnvelope, *(noiseSampleAddress++));
            gb_write(wCurTrackFrequency, *(noiseSampleAddress++));
            curChan->noiseSampling = 1;
        }
    }
}

void ParseMusic(void) {
    uint8_t cmd;
    while (1) {  // parses until a note is read or the song is ended
        cmd = GetMusicByte();
        if ((cmd == sound_ret_cmd) && (!curChan->subroutine)) {  // song end
            if ((curChannel >= NUM_MUSIC_CHANS) || (!chan[curChannel + NUM_MUSIC_CHANS]->channelOn)) {
                if (curChan->cry)
                    RestoreVolume();
                if (curChannel == CHAN5)
                    gb_write(rNR10, 0);
            }
            curChan->channelOn = 0;  // turn channel off
            curChan->rest = 1;       // note = rest
            curChan->musicId = 0;    // clear music id & bank
            curChan->musicBank = 0;
            return;
        } else if (cmd < FIRST_MUSIC_CMD) {  // note
            if (curChan->sfx) {
                ParseSFXOrCry();
            } else if (curChan->cry) {
                ParseSFXOrCry();
            } else if (curChan->noise) {
                GetNoiseSample();
            } else {
                SetNoteDuration(gb_read(wCurMusicByte) & 0xF);  // set note duration (bottom nybble)
                uint8_t note = gb_read(wCurMusicByte) >> 4;     // get note pitch (top nybble)
                if (note) {
                    curChan->pitch = note;                                     // update pitch
                    curChan->frequency = GetFrequency(note, curChan->octave);  // update frequency
                    curChan->noiseSampling = 1;
                    LoadNote();
                } else {
                    curChan->rest = 1;
                }
            }
            return;
        } else {  // not a note or end, keep parsing
            ParseMusicCommand();
        }
    }
}

void RestoreVolume(void) {
    if (curChannel == CHAN5) {  // ch5 only
        chan[CHAN6]->pitchOffset = 0;
        chan[CHAN8]->pitchOffset = 0;
        gb_write(wVolume, gb_read(wLastVolume));
        gb_write(wLastVolume, 0);
        gb_write(wSFXPriority, 0);
    }
}

void ParseSFXOrCry(void) {
    curChan->noiseSampling = 1;                          // turn noise sampling on
    SetNoteDuration(gb_read(wCurMusicByte));             // update note duration
    curChan->volumeEnvelope = GetMusicByte();            // update volume envelope from next param
    uint16_t freq = GetMusicByte();                      // update frequency from next param(s)
    if ((curChannel != CHAN4) && (curChannel != CHAN8))  // are we on the last channel? (noise sampling)
        freq |= GetMusicByte() << 8;
    curChan->frequency = freq;
}

void GetNoiseSample(void) {                                //  load ptr to sample header in noiseSampleAddress
    if ((curChannel == CHAN4) || (curChannel == CHAN8)) {  // are we on the last channel?
        SetNoteDuration(gb_read(wCurMusicByte) & 0xF);     // update note duration
        uint8_t sample;
        if (!(curChannel & (1 << NOISE_CHAN_F))) {  // check current channel
            if (chan[CHAN8]->channelOn) return;     // is ch8 on? (noise)
            sample = gb_read(wMusicNoiseSampleSet);
        } else {
            sample = gb_read(wMusicNoiseSampleSet);
        }
        uint8_t note = gb_read(wCurMusicByte) >> 4;
        if (note) {
            noiseSampleAddress = Drumkits[sample][note];
            gb_write(wNoiseSampleDelay, 0);
        }
    }
}

void ParseMusicCommand(void) {
    static void (*MusicCommands[48])(void) = {Music_Octave,
                                              Music_Octave,
                                              Music_Octave,
                                              Music_Octave,
                                              Music_Octave,
                                              Music_Octave,
                                              Music_Octave,
                                              Music_Octave,
                                              Music_NoteType,
                                              Music_Transpose,
                                              Music_Tempo,
                                              Music_DutyCycle,
                                              Music_VolumeEnvelope,
                                              Music_PitchSweep,
                                              Music_DutyCyclePattern,
                                              Music_ToggleSFX,
                                              Music_PitchSlide,
                                              Music_Vibrato,
                                              MusicE2,
                                              Music_ToggleNoise,
                                              Music_ForceStereoPanning,
                                              Music_Volume,
                                              Music_PitchOffset,
                                              MusicE7,
                                              MusicE8,
                                              Music_TempoRelative,
                                              Music_RestartChannel,
                                              Music_NewSong,
                                              Music_SFXPriorityOn,
                                              Music_SFXPriorityOff,
                                              MusicEE,
                                              Music_StereoPanning,
                                              Music_SFXToggleNoise,
                                              MusicNone,
                                              MusicNone,
                                              MusicNone,
                                              MusicNone,
                                              MusicNone,
                                              MusicNone,
                                              MusicNone,
                                              MusicNone,
                                              MusicNone,
                                              Music_SetCondition,
                                              Music_JumpIf,
                                              Music_Jump,
                                              Music_Loop,
                                              Music_Call,
                                              Music_Ret};

    return MusicCommands[gb_read(wCurMusicByte) - FIRST_MUSIC_CMD]();
}

void MusicNone(void) {
    return;
}

void Music_Ret(void) {
    //  called when $ff is encountered w/ subroutine flag set
    //  end music stream
    //  return to caller of the subroutine
    // reset subroutine flag
    curChan->subroutine = 0;
    curChan->musicAddress = curChan->lastMusicAddress;
}

void Music_Call(void) {
    //  call music stream (subroutine)
    //  parameters: ll hh
    // get pointer from next 2 bytes
    curChan->lastMusicAddress = curChan->musicAddress + 2;  // skip the pointer
    curChan->musicAddress = (GetMusicByte() | (GetMusicByte() << 8));
    curChan->subroutine = 1;
}

void Music_Jump(void) {
    //  jump
    //  parameters: ll hh
    // get pointer from next 2 bytes
    curChan->musicAddress = (GetMusicByte() | (GetMusicByte() << 8));
}

void Music_Loop(void) {
    //  loops xx - 1 times
    //      00: infinite
    //  params: 3
    //     xx ll hh
    //         xx : loop count
    //        ll hh : pointer
    uint8_t loop = GetMusicByte();  // get loop count
    if (!curChan->looping) {        // has the loop been initiated?
        if (!loop) {                // infinite loop
            curChan->musicAddress = (GetMusicByte() | (GetMusicByte() << 8));
            return;
        }
        curChan->looping = 1;
        curChan->loopCount = loop - 1;
    }
    if (!curChan->loopCount--) {
        curChan->looping = 0;  // reset loop flag
        curChan->loopCount = 0;
        curChan->musicAddress += 2;  // skip pointer
    } else
        curChan->musicAddress = (GetMusicByte() | (GetMusicByte() << 8));  // get pointer
}

void Music_SetCondition(void) {
    //  set condition for a jump
    //  used with FB
    //  params: 1
    //     xx
    curChan->condition = GetMusicByte();  // set condition
}

void Music_JumpIf(void) {
    //  conditional jump
    //  used with FA
    //  params: 3
    //      xx: condition
    //     ll hh: pointer
    //  check condition
    // a = condition
    // if existing condition matches, jump to new address
    if (GetMusicByte() == curChan->condition)
        curChan->musicAddress = (GetMusicByte() | (GetMusicByte() << 8));  // get pointer
    else
        curChan->musicAddress += 2;  // skip pointer
}

void MusicEE(void) {
    //  unused
    //  conditional jump
    //  checks a byte in ram corresponding to the current channel
    //  params: 2
    //         ll hh

    //  if ????, jump
    // get channel
    if (channelJumpCondition[curChannel & 3]) {
        channelJumpCondition[curChannel & 3] = 0;  // reset jump flag
        curChan->musicAddress = (GetMusicByte() | (GetMusicByte() << 8));
    } else
        curChan->musicAddress += 2;  // skip pointer
}

void MusicE2(void) {
    //  unused
    //  params: 1
    GetMusicByte();
}

void Music_Vibrato(void) {
    //  vibrato
    //  params: 2
    //     1: [xx]
    // delay in frames
    //     2: [yz]
    // y: extent
    // z: rate (# frames per cycle)
    curChan->vibrato = 1;
    curChan->vibratoDir = 0;
    curChan->vibratoDelay = GetMusicByte();  // update delay
    curChan->vibratoDelayCount = curChan->vibratoDelay;
    uint8_t param = GetMusicByte();
    curChan->vibratoRate = param & 0xF;
    curChan->vibratoRate |= curChan->vibratoRate << 4;  // Use the upper nibble as the reload value
    param >>= 4;
    curChan->vibratoExtent = param >> 1;                                      // half
    curChan->vibratoExtent |= ((curChan->vibratoExtent + (param & 1)) << 4);  // If the extent was an odd number, add one to the upper nibble
}

void Music_PitchSlide(void) {
    //  set the target for pitch slide
    //  params: 2
    //  note duration
    //  target note
    gb_write(wCurNoteDuration, GetMusicByte());
    uint8_t note = GetMusicByte();  // upper nibble is octave, lower is the note
    curChan->pitchSlideTarget = GetFrequency(note & 0xF, note >> 4);
    curChan->pitchSlide = 1;
}

void Music_PitchOffset(void) {
    //  tone
    //  params: 1 (dw)
    //  offset to add to each note frequency
    curChan->pitchOffsetEnabled = 1;
    curChan->pitchOffset = ((GetMusicByte() << 8) | GetMusicByte());  // reverse byte order
}

void MusicE7(void) {
    //  unused
    //  params: 1
    GetMusicByte();
}

void Music_DutyCyclePattern(void) {
    //  sequence of 4 duty cycles to be looped
    //  params: 1 (4 2-bit duty cycle arguments)
    curChan->dutyLoop = 1;
    curChan->dutyCyclePattern = GetMusicByte();
    curChan->dutyCyclePattern = (curChan->dutyCyclePattern >> 2) | (curChan->dutyCyclePattern << 6);
    curChan->dutyCycle = curChan->dutyCyclePattern & 0xC0;
}

void MusicE8(void) {
    //  unused
    //  params: 1
    GetMusicByte();
}

void Music_ToggleSFX(void) {
    //  toggle something
    //  params: none
    curChan->sfx ^= 1;
}

void Music_ToggleNoise(void) {
    //  toggle music noise sampling
    //  can't be used as a straight toggle since the param is not read from on->off
    //  params:
    //      noise on: 1
    //      noise off: 0
    curChan->noise ^= 1;
    if (curChan->noise) gb_write(wMusicNoiseSampleSet, GetMusicByte());
}

void Music_SFXToggleNoise(void) {
    //  toggle sfx noise sampling
    //  params:
    //     on: 1
    //      off: 0
    curChan->noise ^= 1;
    if (curChan->noise) gb_write(wSFXNoiseSampleSet, GetMusicByte());
}

void Music_NoteType(void) {
    //  note length
    //     # frames per 16th note
    //  volume envelope: see Music_VolumeEnvelope
    //  params: 2 (1 if noise channel)
    curChan->noteLength = GetMusicByte();                  // note length
    if ((curChannel & 3) < CHAN4) Music_VolumeEnvelope();  // envelope
}

void Music_PitchSweep(void) {
    //  update pitch sweep
    //  params: 1
    gb_write(wPitchSweep, GetMusicByte());
    curChan->pitchSweep = 1;
}

void Music_DutyCycle(void) {
    //  duty cycle
    //  params: 1
    curChan->dutyCycle = GetMusicByte() << 6;
}

void Music_VolumeEnvelope(void) {
    //  volume envelope
    //  params: 1
    //     hi: volume
    //    lo: fade
    curChan->volumeEnvelope = GetMusicByte();
}

void Music_Tempo(void) {
    //  global tempo
    //  params: 2
    //     de: tempo
    SetGlobalTempo((GetMusicByte() << 8) | GetMusicByte());
}

void Music_Octave(void) {
    //  set octave based on lo nybble of the command
    curChan->octave = gb_read(wCurMusicByte) & 7;
}

void Music_Transpose(void) {
    //  set starting octave
    //  this forces all notes up by the starting octave
    //  params: 1
    curChan->transposition = GetMusicByte();
}

void Music_StereoPanning(void) {
    //  stereo panning
    //  params: 1
    if ((gb_read(wOptions) & (1 << STEREO)))  // stereo on?
        Music_ForceStereoPanning();
    else
        GetMusicByte();  // skip param
}

void Music_ForceStereoPanning(void) {
    //  force panning
    //  params: 1
    SetLRTracks();
    curChan->tracks &= GetMusicByte();
}

void Music_Volume(void) {
    //  set volume
    //  params: 1
    //     see Volume
    uint8_t param = GetMusicByte();
    if (!gb_read(wMusicFade)) gb_write(wVolume, param);  // is the song fading?
}

void Music_TempoRelative(void) {
    //  set global tempo to current channel tempo +/- param
    //  params: 1 signed
    uint8_t param = GetMusicByte();
    if (param & 0x80)
        SetGlobalTempo(curChan->tempo - (param & 0x7F));
    else
        SetGlobalTempo(curChan->tempo + param);
}

void Music_SFXPriorityOn(void) {
    //  turn sfx priority on
    //  params: none
    gb_write(wSFXPriority, 1);
}

void Music_SFXPriorityOff(void) {
    //  turn sfx priority off
    //  params: none
    gb_write(wSFXPriority, 0);
}

void Music_RestartChannel(void) {
    //  restart current channel from channel header (same bank)
    //  params: 2 (5)
    //  ll hh: pointer to new channel header
    //     header format: 0x yy zz
    //         x: channel # (0-3)
    //         zzyy: pointer to new music data
    gb_write16(wMusicID, curChan->musicId);    // update music id
    gb_write(wMusicBank, curChan->musicBank);  // update music bank
    uint16_t pointer = GetMusicByte() | (GetMusicByte() << 8);
    LoadChannel(gb_read16(pointer));
    StartChannel();
}

void Music_NewSong(void) {
    //  new song
    //  params: 2
    //     de: song id
    v_PlayMusic(GetMusicByte() | (GetMusicByte() << 8));
}

uint8_t GetMusicByte(void) {
    //  returns byte from current address in a
    //  advances to next byte in music data
    uint32_t address = (curChan->musicBank << 14) | (curChan->musicAddress & 0x3FFF);
    gb_write(wCurMusicByte, gb.gb_rom_read(address));
    curChan->musicAddress++;
    return gb_read(wCurMusicByte);
}

uint16_t GetFrequency(uint8_t note, uint8_t octave) {
    //  generate frequency
    //  input:
    //      d: octave
    //     e: pitch
    //  output:
    //      frequency
    note += (curChan->transposition & 0xF);
    if (!note) return 0;
    octave += (curChan->transposition >> 4);
    octave = 7 - ((octave > 7) ? 7 : octave);                       // cap octave
    return (((FrequencyTable[note] | 0xF0000) >> octave) & 0x7ff);  // or 0xF0000 to accomodate for higher octaves
}

void SetNoteDuration(uint8_t duration) {
    //  input: note duration in 16ths
    // store delay units in de
    duration++;
    uint16_t result = (((curChan->noteLength * duration) & 0xFF) * curChan->tempo) + curChan->field16;
    curChan->field16 = result & 0xFF;     // store result in fraction
    curChan->noteDuration = result >> 8;  // store result in NoteDuration
}

void SetGlobalTempo(uint16_t tempo) {
    uint8_t ch = (curChannel < NUM_MUSIC_CHANS) ? 0 : NUM_MUSIC_CHANS;
    for (int i = 0; i < NUM_MUSIC_CHANS; i++, ch++) {
        chan[ch]->tempo = tempo;
        chan[ch]->field16 = 0;
    }
}

void StartChannel(void) {
    SetLRTracks();
    chan[curChannel]->channelOn = 1;
}

void SetLRTracks(void) {
    //  set tracks for a the current channel to default
    //  seems to be redundant since this is overwritten by stereo data later
    //  Mono and Stereo appear to initialize the same
    chan[curChannel]->tracks = (1 << (curChannel & 3));
    chan[curChannel]->tracks |= chan[curChannel]->tracks << 4;
}

void v_PlayMusic(uint16_t songId) {
    //  load music
    MusicOff();
    gb_write16(wMusicID, songId);
    LD_HL(mMusic);                  // ld hl, Music
    REG_HL += songId * 3;           // 3-byte pointer
    LD_A_hli;                       // ld a, [hli]
    LD_addr_A(wMusicBank);          // ld [wMusicBank], a
    LD_E_hl;                        // ld e, [hl]
    INC_HL;                         // inc hl
    LD_D_hl;                        // ld d, [hl] ; music header address
    REG_A = LoadMusicByte(REG_DE);  // store first byte of music header in a
    RLCA;                           // rlca
    RLCA;                           // rlca
    maskbits(NUM_MUSIC_CHANS, 0);   // maskbits NUM_MUSIC_CHANS
    INC_A;                          // inc a

loop:
    //  start playing channels
    PUSH_AF;  // push af
    REG_DE = LoadChannel(REG_DE);
    StartChannel();
    POP_AF;           // pop af
    DEC_A;            // dec a
    IF_NZ goto loop;  // jr nz, .loop
    for (int i = 0; i < NUM_MUSIC_CHANS; i++) channelJumpCondition[i] = 0;
    noiseSampleAddress = NULL;
    gb_write(wNoiseSampleDelay, 0);
    gb_write(wMusicNoiseSampleSet, 0);
    MusicOn();
}

void v_PlayCry(void) {
    //  Play cry de using parameters:
    //     wCryPitch
    //     wCryLength

    MusicOff();

    //  Overload the music id with the cry id
    LD_HL(wMusicID);  // ld hl, wMusicID
    LD_hl_E;          // ld [hl], e
    INC_HL;           // inc hl
    LD_hl_D;          // ld [hl], d

    //  3-byte pointers (bank, address)
    LD_HL(mCries);  // ld hl, Cries
    ADD_HL_DE;      // add hl, de
    ADD_HL_DE;      // add hl, de
    ADD_HL_DE;      // add hl, de

    LD_A_hli;               // ld a, [hli]
    LD_addr_A(wMusicBank);  // ld [wMusicBank], a

    LD_E_hl;  // ld e, [hl]
    INC_HL;   // inc hl
    LD_D_hl;  // ld d, [hl]

    //  Read the cry's sound header
    REG_A = LoadMusicByte(REG_DE);
    // Top 2 bits contain the number of channels
    RLCA;                          // rlca
    RLCA;                          // rlca
    maskbits(NUM_MUSIC_CHANS, 0);  // maskbits NUM_MUSIC_CHANS

    //  For each channel:
    INC_A;  // inc a

loop:
    PUSH_AF;                       // push af
    REG_DE = LoadChannel(REG_DE);  // bc = current channel

    LD_HL(CHANNEL_FLAGS1);  // ld hl, CHANNEL_FLAGS1
    ADD_HL_BC;              // add hl, bc
    SET_hl(SOUND_CRY);      // set SOUND_CRY, [hl]

    LD_HL(CHANNEL_FLAGS2);       // ld hl, CHANNEL_FLAGS2
    ADD_HL_BC;                   // add hl, bc
    SET_hl(SOUND_PITCH_OFFSET);  // set SOUND_PITCH_OFFSET, [hl]

    LD_HL(CHANNEL_PITCH_OFFSET);  // ld hl, CHANNEL_PITCH_OFFSET
    ADD_HL_BC;                    // add hl, bc
    LD_A_addr(wCryPitch);         // ld a, [wCryPitch]
    LD_hli_A;                     // ld [hli], a
    LD_A_addr(wCryPitch + 1);     // ld a, [wCryPitch + 1]
    LD_hl_A;                      // ld [hl], a

    //  No tempo for channel 4
    LD_A_addr(wCurChannel);        // ld a, [wCurChannel]
    maskbits(NUM_MUSIC_CHANS, 0);  // maskbits NUM_MUSIC_CHANS
    CP_A(CHAN4);                   // cp CHAN4
    IF_NC goto start;              // jr nc, .start

    //  Tempo is effectively length
    LD_HL(CHANNEL_TEMPO);       // ld hl, CHANNEL_TEMPO
    ADD_HL_BC;                  // add hl, bc
    LD_A_addr(wCryLength);      // ld a, [wCryLength]
    LD_hli_A;                   // ld [hli], a
    LD_A_addr(wCryLength + 1);  // ld a, [wCryLength + 1]
    LD_hl_A;                    // ld [hl], a

start:
    StartChannel();
    LD_A_addr(wStereoPanningMask);  // ld a, [wStereoPanningMask]
    AND_A_A;                        // and a
    IF_Z goto next;                 // jr z, .next

    //  Stereo only: Play cry from the monster's side.
    //  This only applies in-battle.

    LD_A_addr(wOptions);  // ld a, [wOptions]
    BIT_A(STEREO);        // bit STEREO, a
    IF_Z goto next;       // jr z, .next

    //  [CHANNEL_TRACKS] &= [wCryTracks]
    LD_HL(CHANNEL_TRACKS);  // ld hl, CHANNEL_TRACKS
    ADD_HL_BC;              // add hl, bc
    LD_A_hl;                // ld a, [hl]
    LD_HL(wCryTracks);      // ld hl, wCryTracks
    AND_A_hl;               // and [hl]
    LD_HL(CHANNEL_TRACKS);  // ld hl, CHANNEL_TRACKS
    ADD_HL_BC;              // add hl, bc
    LD_hl_A;                // ld [hl], a

next:
    POP_AF;           // pop af
    DEC_A;            // dec a
    IF_NZ goto loop;  // jr nz, .loop

    //  Cries play at max volume, so we save the current volume for later.
    LD_A_addr(wLastVolume);  // ld a, [wLastVolume]
    AND_A_A;                 // and a
    IF_NZ goto end;          // jr nz, .end

    LD_A_addr(wVolume);      // ld a, [wVolume]
    LD_addr_A(wLastVolume);  // ld [wLastVolume], a
    LD_A(MAX_VOLUME);        // ld a, MAX_VOLUME
    LD_addr_A(wVolume);      // ld [wVolume], a

end:
    LD_A(1);                  // ld a, 1 ; stop playing music
    LD_addr_A(wSFXPriority);  // ld [wSFXPriority], a
    MusicOn();
    return;
}

void v_PlaySFX(void) {
    //  clear channels if they aren't already
    MusicOff();
    LD_HL(wChannel5Flags1);    // ld hl, wChannel5Flags1
    BIT_hl(SOUND_CHANNEL_ON);  // bit SOUND_CHANNEL_ON, [hl] ; ch5 on?
    IF_Z goto ch6;             // jr z, .ch6
    RES_hl(SOUND_CHANNEL_ON);  // res SOUND_CHANNEL_ON, [hl] ; turn it off
    XOR_A_A;                   // xor a
    LDH_addr_A(rNR11);         // ldh [rNR11], a ; length/wavepattern = 0
    LD_A(0x8);                 // ld a, $8
    LDH_addr_A(rNR12);         // ldh [rNR12], a ; envelope = 0
    XOR_A_A;                   // xor a
    LDH_addr_A(rNR13);         // ldh [rNR13], a ; frequency lo = 0
    LD_A(0x80);                // ld a, $80
    LDH_addr_A(rNR14);         // ldh [rNR14], a ; restart sound (freq hi = 0)
    XOR_A_A;                   // xor a
    LD_addr_A(wPitchSweep);    // ld [wPitchSweep], a ; pitch sweep off
    LDH_addr_A(rNR10);         // ldh [rNR10], a ; pitch sweep off

ch6:
    LD_HL(wChannel6Flags1);    // ld hl, wChannel6Flags1
    BIT_hl(SOUND_CHANNEL_ON);  // bit SOUND_CHANNEL_ON, [hl]
    IF_Z goto ch7;             // jr z, .ch7
    RES_hl(SOUND_CHANNEL_ON);  // res SOUND_CHANNEL_ON, [hl] ; turn it off
    XOR_A_A;                   // xor a
    LDH_addr_A(rNR21);         // ldh [rNR21], a ; length/wavepattern = 0
    LD_A(0x8);                 // ld a, $8
    LDH_addr_A(rNR22);         // ldh [rNR22], a ; envelope = 0
    XOR_A_A;                   // xor a
    LDH_addr_A(rNR23);         // ldh [rNR23], a ; frequency lo = 0
    LD_A(0x80);                // ld a, $80
    LDH_addr_A(rNR24);         // ldh [rNR24], a ; restart sound (freq hi = 0)

ch7:
    LD_HL(wChannel7Flags1);    // ld hl, wChannel7Flags1
    BIT_hl(SOUND_CHANNEL_ON);  // bit SOUND_CHANNEL_ON, [hl]
    IF_Z goto ch8;             // jr z, .ch8
    RES_hl(SOUND_CHANNEL_ON);  // res SOUND_CHANNEL_ON, [hl] ; turn it off
    XOR_A_A;                   // xor a
    LDH_addr_A(rNR30);         // ldh [rNR30], a ; sound mode #3 off
    LDH_addr_A(rNR31);         // ldh [rNR31], a ; length/wavepattern = 0
    LD_A(0x8);                 // ld a, $8
    LDH_addr_A(rNR32);         // ldh [rNR32], a ; envelope = 0
    XOR_A_A;                   // xor a
    LDH_addr_A(rNR33);         // ldh [rNR33], a ; frequency lo = 0
    LD_A(0x80);                // ld a, $80
    LDH_addr_A(rNR34);         // ldh [rNR34], a ; restart sound (freq hi = 0)

ch8:
    LD_HL(wChannel8Flags1);    // ld hl, wChannel8Flags1
    BIT_hl(SOUND_CHANNEL_ON);  // bit SOUND_CHANNEL_ON, [hl]
    IF_Z goto chscleared;      // jr z, .chscleared
    RES_hl(SOUND_CHANNEL_ON);  // res SOUND_CHANNEL_ON, [hl] ; turn it off
    XOR_A_A;                   // xor a
    LDH_addr_A(rNR41);         // ldh [rNR41], a ; length/wavepattern = 0
    LD_A(0x8);                 // ld a, $8
    LDH_addr_A(rNR42);         // ldh [rNR42], a ; envelope = 0
    XOR_A_A;                   // xor a
    LDH_addr_A(rNR43);         // ldh [rNR43], a ; frequency lo = 0
    LD_A(0x80);                // ld a, $80
    LDH_addr_A(rNR44);         // ldh [rNR44], a ; restart sound (freq hi = 0)
    XOR_A_A;                   // xor a
    noiseSampleAddress = NULL;

chscleared:
    //  start reading sfx header for # chs
    LD_HL(wMusicID);        // ld hl, wMusicID
    LD_hl_E;                // ld [hl], e
    INC_HL;                 // inc hl
    LD_hl_D;                // ld [hl], d
    LD_HL(mSFX);            // ld hl, SFX
    ADD_HL_DE;              // add hl, de ; three
    ADD_HL_DE;              // add hl, de ; byte
    ADD_HL_DE;              // add hl, de ; pointers
                            // get bank
    LD_A_hli;               // ld a, [hli]
    LD_addr_A(wMusicBank);  // ld [wMusicBank], a
                            // get address
    LD_E_hl;                // ld e, [hl]
    INC_HL;                 // inc hl
    LD_D_hl;                // ld d, [hl]
                            // get # channels
    REG_A = LoadMusicByte(REG_DE);
    RLCA;                          // rlca ; top 2
    RLCA;                          // rlca ; bits
    maskbits(NUM_MUSIC_CHANS, 0);  // maskbits NUM_MUSIC_CHANS
    INC_A;                         // inc a ; # channels -> # loops

startchannels:
    PUSH_AF;                       // push af
    REG_DE = LoadChannel(REG_DE);  // bc = current channel
    LD_HL(CHANNEL_FLAGS1);         // ld hl, CHANNEL_FLAGS1
    ADD_HL_BC;                     // add hl, bc
    SET_hl(SOUND_SFX);             // set SOUND_SFX, [hl]
    StartChannel();
    POP_AF;                    // pop af
    DEC_A;                     // dec a
    IF_NZ goto startchannels;  // jr nz, .startchannels
    MusicOn();
    XOR_A_A;                  // xor a
    LD_addr_A(wSFXPriority);  // ld [wSFXPriority], a
    return;
}

void PlayStereoSFX(void) {
    //  play sfx de

    MusicOff();

    //  standard procedure if stereo's off
    LD_A_addr(wOptions);      // ld a, [wOptions]
    BIT_A(STEREO);            // bit STEREO, a
    IF_Z return v_PlaySFX();  // jp z, _PlaySFX

    //  else, let's go ahead with this
    LD_HL(wMusicID);  // ld hl, wMusicID
    LD_hl_E;          // ld [hl], e
    INC_HL;           // inc hl
    LD_hl_D;          // ld [hl], d

    //  get sfx ptr
    LD_HL(mSFX);  // ld hl, SFX
    ADD_HL_DE;    // add hl, de
    ADD_HL_DE;    // add hl, de
    ADD_HL_DE;    // add hl, de

    //  bank
    LD_A_hli;               // ld a, [hli]
    LD_addr_A(wMusicBank);  // ld [wMusicBank], a
                            //  address
    LD_E_hl;                // ld e, [hl]
    INC_HL;                 // inc hl
    LD_D_hl;                // ld d, [hl]

    //  bit 2-3
    REG_A = LoadMusicByte(REG_DE);
    RLCA;                          // rlca
    RLCA;                          // rlca
    maskbits(NUM_MUSIC_CHANS, 0);  // maskbits NUM_MUSIC_CHANS
    INC_A;                         // inc a

loop:
    PUSH_AF;  // push af
    REG_DE = LoadChannel(REG_DE);

    LD_HL(CHANNEL_FLAGS1);  // ld hl, CHANNEL_FLAGS1
    ADD_HL_BC;              // add hl, bc
    SET_hl(SOUND_SFX);      // set SOUND_SFX, [hl]

    PUSH_DE;                       // push de
                                   // get tracks for this channel
    LD_A_addr(wCurChannel);        // ld a, [wCurChannel]
    maskbits(NUM_MUSIC_CHANS, 0);  // maskbits NUM_MUSIC_CHANS
    LD_E_A;                        // ld e, a
    LD_D(0);                       // ld d, 0
    GetLRTracks();
    ADD_HL_DE;                  // add hl, de
    LD_A_hl;                    // ld a, [hl]
    LD_HL(wStereoPanningMask);  // ld hl, wStereoPanningMask
    AND_A_hl;                   // and [hl]

    LD_HL(CHANNEL_TRACKS);  // ld hl, CHANNEL_TRACKS
    ADD_HL_BC;              // add hl, bc
    LD_hl_A;                // ld [hl], a

    LD_HL(CHANNEL_FIELD30);  // ld hl, CHANNEL_FIELD30
    ADD_HL_BC;               // add hl, bc
    LD_hl_A;                 // ld [hl], a

    LD_A_addr(wCryTracks);  // ld a, [wCryTracks]
    CP_A(2);                // cp 2 ; ch 1-2
    IF_C goto skip;         // jr c, .skip

    //  ch3-4
    LD_A_addr(wSFXDuration);  // ld a, [wSFXDuration]

    LD_HL(CHANNEL_FIELD2E);  // ld hl, CHANNEL_FIELD2E
    ADD_HL_BC;               // add hl, bc
    LD_hl_A;                 // ld [hl], a

    LD_HL(CHANNEL_FIELD2F);  // ld hl, CHANNEL_FIELD2F
    ADD_HL_BC;               // add hl, bc
    LD_hl_A;                 // ld [hl], a

    LD_HL(CHANNEL_FLAGS2);  // ld hl, CHANNEL_FLAGS2
    ADD_HL_BC;              // add hl, bc
    SET_hl(SOUND_UNKN_0F);  // set SOUND_UNKN_0F, [hl]

skip:
    POP_DE;  // pop de

    //  turn channel on
    LD_HL(CHANNEL_FLAGS1);     // ld hl, CHANNEL_FLAGS1
    ADD_HL_BC;                 // add hl, bc
    SET_hl(SOUND_CHANNEL_ON);  // set SOUND_CHANNEL_ON, [hl] ; on

    //  done?
    POP_AF;           // pop af
    DEC_A;            // dec a
    IF_NZ goto loop;  // jr nz, .loop

    //  we're done
    MusicOn();
    return;
}

uint16_t LoadChannel(uint16_t pointer) {
    //  input: audio pointer
    //  sets bc to current channel pointer
    curChannel = LoadMusicByte(pointer++) & 7;
    gb_write(wCurChannel, curChannel);
    chan[curChannel]->channelOn = 0;  // channel off
    ChannelInit(curChannel);
    chan[curChannel]->musicAddress = LoadMusicByte(pointer) | (LoadMusicByte(pointer + 1) << 8);  // load music pointer
    pointer += 2;
    chan[curChannel]->musicId = gb_read16(wMusicID);      // load music id
    chan[curChannel]->musicBank = gb_read16(wMusicBank);  // load music bank
    return pointer;
}

void ChannelInit(uint8_t channel) {
    REG_BC = channelPointers[channel];  // ld hl, ChannelPointers
    //  make sure channel is cleared
    //  set default tempo and note length in case nothing is loaded
    //  input:
    //    bc = channel struct pointer
    PUSH_DE;                      // push de
    XOR_A_A;                      // xor a
                                  // get channel struct location and length
    LD_HL(CHANNEL_MUSIC_ID);      // ld hl, CHANNEL_MUSIC_ID ; start
    ADD_HL_BC;                    // add hl, bc
    LD_E(CHANNEL_STRUCT_LENGTH);  // ld e, CHANNEL_STRUCT_LENGTH ; channel struct length
    // clear channel

loop:
    LD_hli_A;                       // ld [hli], a
    DEC_E;                          // dec e
    IF_NZ goto loop;                // jr nz, .loop
    chan[channel]->tempo = 0x100;   // set tempo to default ($100)
    chan[channel]->noteLength = 1;  // set note length to default ($1) (fast)
    POP_DE;                         // pop de
}

uint8_t LoadMusicByte(uint16_t pointer) {
    //  input:
    //    de = current music address
    //  output:
    //    a = wCurMusicByte
    uint32_t address = (gb_read(wMusicBank) << 14) | (pointer & 0x3FFF);
    gb_write(wCurMusicByte, gb.gb_rom_read(address));
    return gb_read(wCurMusicByte);
}

void GetLRTracks(void) {
    //  gets the default sound l/r channels
    //  stores mono/stereo table in hl
    LD_A_addr(wOptions);  // ld a, [wOptions]
    BIT_A(STEREO);        // bit STEREO, a
                          // made redundant, could have had a purpose in gold
    IF_NZ goto stereo;    // jr nz, .stereo
    LD_HL(mMonoTracks);   // ld hl, MonoTracks
    return;

stereo:
    LD_HL(mStereoTracks);  // ld hl, StereoTracks
    return;
}

void ClearChannels(void) {
    //  runs ClearChannel for all 4 channels
    //  doesn't seem to be used, but functionally identical to InitSound
    static uint16_t noiseReg[4] = {rNR10,
                                   rNR20,
                                   rNR30,
                                   rNR40};
    gb_write(rNR50, 0);
    gb_write(rNR51, 0);
    gb_write(rNR52, 0x80);
    for (int i = 0; i < NUM_MUSIC_CHANS; i++)
        ClearChannel(noiseReg[i]);
}

void ClearChannel(uint16_t nReg) {
    //  input: hl = beginning hw sound register (rNR10, rNR20, rNR30, rNR40)
    //  output: 00 00 80 00 80

    //    sound channel            1      2      3      4
    gb_write(nReg++, 0);     // rNR10, rNR20, rNR30, rNR40 ; sweep = 0
    gb_write(nReg++, 0);     // rNR11, rNR21, rNR31, rNR41 ; length/wavepattern = 0
    gb_write(nReg++, 8);     // rNR12, rNR22, rNR32, rNR42 ; envelope = 0
    gb_write(nReg++, 0);     // rNR13, rNR23, rNR33, rNR43 ; frequency lo = 0
    gb_write(nReg++, 0x80);  // rNR14, rNR24, rNR34, rNR44 ; restart sound (freq hi = 0)
}

void PlayTrainerEncounterMusic(void) {
    SET_PC(0xE900AU);
    //  input: e = trainer type
    // turn fade off
    XOR_A_A;                        // xor a
    LD_addr_A(wMusicFade);          // ld [wMusicFade], a
                                    // play nothing for one frame
    PUSH_DE;                        // push de
    LD_DE(MUSIC_NONE);              // ld de, MUSIC_NONE
    CALL(aPlayMusic);               // call PlayMusic
    CALL(mDelayFrame);              // call DelayFrame
                                    // play new song
    CALL(aMaxVolume);               // call MaxVolume
    POP_DE;                         // pop de
    LD_D(0x00);                     // ld d, $00
    LD_HL(mTrainerEncounterMusic);  // ld hl, TrainerEncounterMusic
    ADD_HL_DE;                      // add hl, de
    LD_E_hl;                        // ld e, [hl]
    CALL(aPlayMusic);               // call PlayMusic
    RET;                            // ret
}
