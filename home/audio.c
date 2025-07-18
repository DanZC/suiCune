#include "../constants.h"
#include "audio.h"
#include "../audio/engine.h"
#include "delay.h"
#include "map.h"
#include "vblank.h"
#include "../data/pokemon/cries.h"

extern struct Channel *chan[8];

static uint16_t SpecialMapMusic(void);
static uint16_t GetMapMusic_MaybeSpecial(void);

//  Audio interfaces.

void InitSound(void) {
    v_InitSound();  // call _InitSound
    // RET;            // ret
}

void UpdateSound(void) {
    // PUSH_HL;  // push hl
    // PUSH_DE;  // push de
    // PUSH_BC;  // push bc
    // PUSH_AF;  // push af

    // LDH_A_addr(hROMBank);        // ldh a, [hROMBank]
    // PUSH_AF;                     // push af
    // LD_A(BANK(av_UpdateSound));  // ld a, BANK(_UpdateSound)
    // LDH_addr_A(hROMBank);        // ldh [hROMBank], a
    // LD_addr_A(MBC3RomBank);      // ld [MBC3RomBank], a

    v_UpdateSound();  // call _UpdateSound

    // POP_AF;                  // pop af
    // LDH_addr_A(hROMBank);    // ldh [hROMBank], a
    // LD_addr_A(MBC3RomBank);  // ld [MBC3RomBank], a

    // POP_AF;  // pop af
    // POP_BC;  // pop bc
    // POP_DE;  // pop de
    // POP_HL;  // pop hl
    // RET;     // ret
}

void PlayMusic(uint16_t music) {
    // PUSH_HL;  // push hl
    // PUSH_DE;  // push de
    // PUSH_BC;  // push bc
    // PUSH_AF;  // push af

    // LDH_A_addr(hROMBank);      // ldh a, [hROMBank]
    // PUSH_AF;                   // push af
    uint8_t oldbank = hram.hROMBank;
    // LD_A(BANK(av_PlayMusic));  // ld a, BANK(_PlayMusic) ; aka BANK(_InitSound)
    // LDH_addr_A(hROMBank);      // ldh [hROMBank], a
    hram.hROMBank = BANK(av_PlayMusic);
    // LD_addr_A(MBC3RomBank);    // ld [MBC3RomBank], a
    gb_write(MBC3RomBank, BANK(av_PlayMusic));

    // LD_A_E;             // ld a, e
    // AND_A_A;            // and a
    // IF_Z goto nomusic;  // jr z, .nomusic
    if(LOW(music) == 0) {
        v_InitSound();  // call _InitSound
    }
    else {
        v_PlayMusic(music);
    }
    // goto end;  // jr .end

// end:
    // POP_AF;                  // pop af
    // LDH_addr_A(hROMBank);    // ldh [hROMBank], a
    hram.hROMBank = oldbank;
    // LD_addr_A(MBC3RomBank);  // ld [MBC3RomBank], a
    gb_write(MBC3RomBank, oldbank);
    // POP_AF;                  // pop af
    // POP_BC;                  // pop bc
    // POP_DE;                  // pop de
    // POP_HL;                  // pop hl
    // RET;                     // ret
}

//  Stop playing music, then play music de.
void PlayMusic2(uint16_t de) {
    // SET_PC(0x3DB9U);
    // PUSH_HL;  // push hl
    // PUSH_DE;  // push de
    // PUSH_BC;  // push bc
    // PUSH_AF;  // push af

    // LDH_A_addr(hROMBank);      // ldh a, [hROMBank]
    // PUSH_AF;                   // push af
    uint8_t oldbank = hram.hROMBank;
    // LD_A(BANK(av_PlayMusic));  // ld a, BANK(_PlayMusic)
    // LDH_addr_A(hROMBank);      // ldh [hROMBank], a
    hram.hROMBank = BANK(av_PlayMusic);
    // LD_addr_A(MBC3RomBank);    // ld [MBC3RomBank], a
    gb_write(MBC3RomBank, BANK(av_PlayMusic));

    // PUSH_DE;  // push de
    v_PlayMusic(MUSIC_NONE);
    // CALL(aDelayFrame);  // call DelayFrame
    DelayFrame();
    // POP_DE;             // pop de
    v_PlayMusic(de);

    // POP_AF;                  // pop af
    // LDH_addr_A(hROMBank);    // ldh [hROMBank], a
    hram.hROMBank = oldbank;
    // LD_addr_A(MBC3RomBank);  // ld [MBC3RomBank], a
    gb_write(MBC3RomBank, oldbank);

    // POP_AF;  // pop af
    // POP_BC;  // pop bc
    // POP_DE;  // pop de
    // POP_HL;  // pop hl
    // RET;     // ret
}

void PlayCry(uint16_t de) {
    //  Play cry de.

    // PUSH_HL;  // push hl
    // PUSH_DE;  // push de
    // PUSH_BC;  // push bc
    // PUSH_AF;  // push af

    // LDH_A_addr(hROMBank);  // ldh a, [hROMBank]
    // PUSH_AF;               // push af

    // ; Cries are stuck in one bank.
    // LD_A(BANK(aPokemonCries));  // ld a, BANK(PokemonCries)
    // LDH_addr_A(hROMBank);       // ldh [hROMBank], a
    // LD_addr_A(MBC3RomBank);     // ld [MBC3RomBank], a

    // LD_HL(mPokemonCries);  // ld hl, PokemonCries
    // for (int rept = 0; rept < MON_CRY_LENGTH; rept++) {
    //     ADD_HL_DE;  // add hl, de
    // }

    // LD_E_hl;  // ld e, [hl]
    // INC_HL;   // inc hl
    // LD_D_hl;  // ld d, [hl]
    // INC_HL;   // inc hl
    const struct PokemonCry* cry = PokemonCries + de;

    // LD_A_hli;                   // ld a, [hli]
    // LD_addr_A(wCryPitch);       // ld [wCryPitch], a
    // LD_A_hli;                   // ld a, [hli]
    // LD_addr_A(wCryPitch + 1);   // ld [wCryPitch + 1], a
    wram->wCryPitch = cry->pitch;
    // LD_A_hli;                   // ld a, [hli]
    // LD_addr_A(wCryLength);      // ld [wCryLength], a
    // LD_A_hl;                    // ld a, [hl]
    // LD_addr_A(wCryLength + 1);  // ld [wCryLength + 1], a
    wram->wCryLength = cry->length;

    // LD_A(BANK(av_PlayCry));  // ld a, BANK(_PlayCry)
    // LDH_addr_A(hROMBank);    // ldh [hROMBank], a
    // LD_addr_A(MBC3RomBank);  // ld [MBC3RomBank], a

    v_PlayCry(cry->index);  // call _PlayCry

    // POP_AF;                  // pop af
    // LDH_addr_A(hROMBank);    // ldh [hROMBank], a
    // LD_addr_A(MBC3RomBank);  // ld [MBC3RomBank], a

    // POP_AF;  // pop af
    // POP_BC;  // pop bc
    // POP_DE;  // pop de
    // POP_HL;  // pop hl
    // RET;     // ret
}

//  Play sound effect de.
//  Sound effects are ordered by priority (highest to lowest)
void PlaySFX(uint16_t de) {
    // PUSH_HL;  // push hl
    // PUSH_DE;  // push de
    // PUSH_BC;  // push bc
    // PUSH_AF;  // push af

    // ; Is something already playing?
    // CALL(aCheckSFX);  // call CheckSFX
    // IF_NC goto play;  // jr nc, .play
        // ; Does it have priority?
        // LD_A_addr(wCurSFX);  // ld a, [wCurSFX]
        // CP_A_E;              // cp e
        // IF_C goto done;      // jr c, .done
    if(!CheckSFX() || (wram->wCurSFX >= LOW(de))) {
        // LDH_A_addr(hROMBank);    // ldh a, [hROMBank]
        // PUSH_AF;                 // push af
        // LD_A(BANK(av_PlaySFX));  // ld a, BANK(_PlaySFX)
        // LDH_addr_A(hROMBank);    // ldh [hROMBank], a
        // LD_addr_A(MBC3RomBank);  // ld [MBC3RomBank], a
        uint8_t oldbank = hram.hROMBank;
        hram.hROMBank = BANK(av_PlaySFX);
        gb_write(MBC3RomBank, hram.hROMBank);

        // LD_A_E;              // ld a, e
        // LD_addr_A(wCurSFX);  // ld [wCurSFX], a
        wram->wCurSFX = LOW(de);
        // REG_DE = de;
        v_PlaySFX(de);         // call _PlaySFX

        // POP_AF;                  // pop af
        // LDH_addr_A(hROMBank);    // ldh [hROMBank], a
        // LD_addr_A(MBC3RomBank);  // ld [MBC3RomBank], a
        hram.hROMBank = oldbank;
        gb_write(MBC3RomBank, oldbank);
    }

    // POP_AF;  // pop af
    // POP_BC;  // pop bc
    // POP_DE;  // pop de
    // POP_HL;  // pop hl
    // RET;     // ret
}

void WaitPlaySFX(uint16_t de) {
    // WaitSFX();
    WaitSFX();
    // CALL(aPlaySFX);  // call PlaySFX
    PlaySFX(de);
    // RET;             // ret
}

// infinite loop until sfx is done playing
void WaitSFX(void) {  
    while (1) {
        if ((!chan[CHAN5]->channelOn) &&
            (!chan[CHAN6]->channelOn) &&
            (!chan[CHAN7]->channelOn) &&
            (!chan[CHAN8]->channelOn)) break;
        gb.display.WY = gb.gb_reg.WY;
        gb.display.window_clear = 0;
        gb_finish_frame();
        VBlank();
    }
}

//  Return false if no sound effect is playing.
// The inverse of CheckSFX.
bool IsSFXPlaying(void) {
    return (chan[CHAN5]->channelOn)
        || (chan[CHAN6]->channelOn)
        || (chan[CHAN7]->channelOn)
        || (chan[CHAN8]->channelOn);
}

void MaxVolume(void) {
    // LD_A(MAX_VOLUME);    // ld a, MAX_VOLUME
    // LD_addr_A(wVolume);  // ld [wVolume], a
    // RET;                 // ret
    wram->wVolume = MAX_VOLUME;
}

void LowVolume(void) {
    // LD_A(0x33);          // ld a, $33 ; 50%
    // LD_addr_A(wVolume);  // ld [wVolume], a
    wram->wVolume = 0x33;
    // RET;                 // ret
}

void MinVolume(void) {
    // XOR_A_A;             // xor a
    // LD_addr_A(wVolume);  // ld [wVolume], a
    // RET;                 // ret
    wram->wVolume = 0;
}

void FadeOutToMusic(void) {
    //  //  unreferenced
    // LD_A(4);                // ld a, 4
    // LD_addr_A(wMusicFade);  // ld [wMusicFade], a
    // RET;                    // ret
}

void FadeInToMusic(void) {
    // LD_A(4 | (1 << MUSIC_FADE_IN_F));  // ld a, 4 | (1 << MUSIC_FADE_IN_F)
    // LD_addr_A(wMusicFade);             // ld [wMusicFade], a
    // RET;                               // ret
    wram->wMusicFade = 4 | (1 << MUSIC_FADE_IN_F);
}

//  Skip a frames of music.
void SkipMusic(uint8_t a) {
    while(a) {
    // loop:
        // AND_A_A;             // and a
        // RET_Z;               // ret z
        // DEC_A;               // dec a
        --a;
        // CALL(aUpdateSound);  // call UpdateSound
        UpdateSound();
        // goto loop;           // jr .loop
    }
}

void FadeToMapMusic(void) {
    // PUSH_HL;  // push hl
    // PUSH_DE;  // push de
    // PUSH_BC;  // push bc
    // PUSH_AF;  // push af

    // CALL(aGetMapMusic_MaybeSpecial);  // call GetMapMusic_MaybeSpecial
    // LD_A_addr(wMapMusic);             // ld a, [wMapMusic]
    // CP_A_E;                           // cp e
    // IF_Z goto done;                   // jr z, .done
    uint16_t music = GetMapMusic_MaybeSpecial();
    if(music == wram->wMapMusic)
        return;

    // LD_A(8);                      // ld a, 8
    // LD_addr_A(wMusicFade);        // ld [wMusicFade], a
    wram->wMusicFade = 8;
    // LD_A_E;                       // ld a, e
    // LD_addr_A(wMusicFadeID);      // ld [wMusicFadeID], a
    // LD_A_D;                       // ld a, d
    // LD_addr_A(wMusicFadeID + 1);  // ld [wMusicFadeID + 1], a
    wram->wMusicFadeID = music;
    // LD_A_E;                       // ld a, e
    // LD_addr_A(wMapMusic);         // ld [wMapMusic], a
    wram->wMapMusic = (uint8_t)music;

// done:
    // POP_AF;  // pop af
    // POP_BC;  // pop bc
    // POP_DE;  // pop de
    // POP_HL;  // pop hl
    // RET;     // ret
}

void PlayMapMusic(void) {
    // SET_PC(0x3E9DU);
    // PUSH_HL;  // push hl
    // PUSH_DE;  // push de
    // PUSH_BC;  // push bc
    // PUSH_AF;  // push af

    // CALL(aGetMapMusic_MaybeSpecial);  // call GetMapMusic_MaybeSpecial
    // LD_A_addr(wMapMusic);             // ld a, [wMapMusic]
    // CP_A_E;                           // cp e
    // IF_Z goto done;                   // jr z, .done
    uint16_t music = GetMapMusic_MaybeSpecial();
    if(music == wram->wMapMusic)
        return;

    // PUSH_DE;               // push de
    // LD_DE(MUSIC_NONE);     // ld de, MUSIC_NONE
    // CALL(aPlayMusic);      // call PlayMusic
    PlayMusic(MUSIC_NONE);
    // CALL(aDelayFrame);     // call DelayFrame
    DelayFrame();
    // POP_DE;                // pop de
    // LD_A_E;                // ld a, e
    // LD_addr_A(wMapMusic);  // ld [wMapMusic], a
    wram->wMapMusic = (uint8_t)(music & 0xff);
    // CALL(aPlayMusic);      // call PlayMusic
    PlayMusic(music);

// done:
    // SET_PC(0x3EBCU);
    // POP_AF;  // pop af
    // POP_BC;  // pop bc
    // POP_DE;  // pop de
    // POP_HL;  // pop hl
    // RET;     // ret
}

void PlayMapMusicBike(void) {
    // SET_PC(0x3EC1U);
    //  If the player's on a bike, play the bike music instead of the map music
    // PUSH_HL;  // push hl
    // PUSH_DE;  // push de
    // PUSH_BC;  // push bc
    // PUSH_AF;  // push af

    // XOR_A_A;                               // xor a
    // LD_addr_A(wDontPlayMapMusicOnReload);  // ld [wDontPlayMapMusicOnReload], a
    wram->wDontPlayMapMusicOnReload = FALSE;
    // LD_DE(MUSIC_BICYCLE);                  // ld de, MUSIC_BICYCLE
    // LD_A_addr(wPlayerState);               // ld a, [wPlayerState]
    // CP_A(PLAYER_BIKE);                     // cp PLAYER_BIKE
    // IF_Z goto play;                        // jr z, .play
    // CALL(aGetMapMusic_MaybeSpecial);       // call GetMapMusic_MaybeSpecial
    uint16_t music;
    if(gPlayer.playerState == PLAYER_BIKE)
        music = MUSIC_BICYCLE;
    else
        music = GetMapMusic_MaybeSpecial();

// play:
    // SET_PC(0x3ED6U);
    // PUSH_DE;            // push de
    // LD_DE(MUSIC_NONE);  // ld de, MUSIC_NONE
    // CALL(aPlayMusic);   // call PlayMusic
    PlayMusic(MUSIC_NONE);
    // CALL(aDelayFrame);  // call DelayFrame
    DelayFrame();
    // POP_DE;             // pop de

    // LD_A_E;                // ld a, e
    // LD_addr_A(wMapMusic);  // ld [wMapMusic], a
    wram->wMapMusic = (uint8_t)(music & 0xff);
    // CALL(aPlayMusic);      // call PlayMusic
    PlayMusic(music);

    // POP_AF;  // pop af
    // POP_BC;  // pop bc
    // POP_DE;  // pop de
    // POP_HL;  // pop hl
    // RET;     // ret
}

void TryRestartMapMusic(void) {
    // SET_PC(0x3EEDU);
    // LD_A_addr(wDontPlayMapMusicOnReload);  // ld a, [wDontPlayMapMusicOnReload]
    // AND_A_A;                               // and a
    // JR_Z(mRestartMapMusic);                // jr z, RestartMapMusic
    if(!wram->wDontPlayMapMusicOnReload)
        return RestartMapMusic();
    // XOR_A_A;                               // xor a
    // LD_addr_A(wMapMusic);                  // ld [wMapMusic], a
    wram->wMapMusic = 0;
    // LD_DE(MUSIC_NONE);                     // ld de, MUSIC_NONE
    // CALL(aPlayMusic);                      // call PlayMusic
    PlayMusic(MUSIC_NONE);
    // CALL(aDelayFrame);                     // call DelayFrame
    DelayFrame();
    // XOR_A_A;                               // xor a
    // LD_addr_A(wDontPlayMapMusicOnReload);  // ld [wDontPlayMapMusicOnReload], a
    wram->wDontPlayMapMusicOnReload = FALSE;
    // RET;                                   // ret
}

void RestartMapMusic(void) {
    // SET_PC(0x3F05U);
    // PUSH_HL;               // push hl
    // PUSH_DE;               // push de
    // PUSH_BC;               // push bc
    // PUSH_AF;               // push af
    // LD_DE(MUSIC_NONE);     // ld de, MUSIC_NONE
    // CALL(aPlayMusic);      // call PlayMusic
    PlayMusic(MUSIC_NONE);
    // CALL(aDelayFrame);     // call DelayFrame
    DelayFrame();
    // LD_A_addr(wMapMusic);  // ld a, [wMapMusic]
    // LD_E_A;                // ld e, a
    // LD_D(0);               // ld d, 0
    // CALL(aPlayMusic);      // call PlayMusic
    PlayMusic(wram->wMapMusic);
    // POP_AF;                // pop af
    // POP_BC;                // pop bc
    // POP_DE;                // pop de
    // POP_HL;                // pop hl
    // RET;                   // ret
}

static uint16_t SpecialMapMusic(void) {
    // LD_A_addr(wPlayerState);  // ld a, [wPlayerState]
    // CP_A(PLAYER_SURF);        // cp PLAYER_SURF
    // IF_Z goto surf;           // jr z, .surf
    // CP_A(PLAYER_SURF_PIKA);   // cp PLAYER_SURF_PIKA
    // IF_Z goto surf;           // jr z, .surf
    if(gPlayer.playerState == PLAYER_SURF || gPlayer.playerState == PLAYER_SURF_PIKA) {
    // surf:
        // LD_DE(MUSIC_SURF);  // ld de, MUSIC_SURF
        // SCF;                // scf
        // RET;                // ret
        return MUSIC_SURF;
    }

    // LD_A_addr(wStatusFlags2);                 // ld a, [wStatusFlags2]
    // BIT_A(STATUSFLAGS2_BUG_CONTEST_TIMER_F);  // bit STATUSFLAGS2_BUG_CONTEST_TIMER_F, a
    // IF_NZ goto contest;                       // jr nz, .contest
    if(bit_test(gPlayer.statusFlags2, STATUSFLAGS2_BUG_CONTEST_TIMER_F)) {
    // contest:
        // LD_A_addr(wMapGroup);                     // ld a, [wMapGroup]
        // CP_A(GROUP_ROUTE_35_NATIONAL_PARK_GATE);  // cp GROUP_ROUTE_35_NATIONAL_PARK_GATE
        // IF_NZ goto no;                            // jr nz, .no
        // LD_A_addr(wMapNumber);                    // ld a, [wMapNumber]
        // CP_A(MAP_ROUTE_35_NATIONAL_PARK_GATE);    // cp MAP_ROUTE_35_NATIONAL_PARK_GATE
        // IF_Z goto ranking;                        // jr z, .ranking
        // CP_A(MAP_ROUTE_36_NATIONAL_PARK_GATE);    // cp MAP_ROUTE_36_NATIONAL_PARK_GATE
        // IF_NZ goto no;                            // jr nz, .no
        if(gCurMapData.mapGroup == GROUP_ROUTE_35_NATIONAL_PARK_GATE 
        && (gCurMapData.mapNumber == MAP_ROUTE_35_NATIONAL_PARK_GATE || gCurMapData.mapNumber == MAP_ROUTE_36_NATIONAL_PARK_GATE)) {
            return MUSIC_BUG_CATCHING_CONTEST_RANKING;
        }

    // ranking:
        // LD_DE(MUSIC_BUG_CATCHING_CONTEST_RANKING);  // ld de, MUSIC_BUG_CATCHING_CONTEST_RANKING
        // SCF;                                        // scf
        // RET;                                        // ret
    }

// no:
    // AND_A_A;  // and a
    // RET;      // ret
    return MUSIC_NONE;

// bike:
    //
    // LD_DE(MUSIC_BICYCLE);  // ld de, MUSIC_BICYCLE
    // SCF;                   // scf
    // RET;                   // ret
}

static uint16_t GetMapMusic_MaybeSpecial(void) {
    // CALL(aSpecialMapMusic);  // call SpecialMapMusic
    // RET_C;                   // ret c
    uint16_t music = SpecialMapMusic();
    if(music != MUSIC_NONE)
        return music;
    // CALL(aGetMapMusic);      // call GetMapMusic
    // RET;                     // ret
    return GetMapMusic();
}

void PlaceBCDNumberSprite(void) {
    //  //  unreferenced
    //  Places a BCD number at the upper center of the screen.
    // LD_A(4 * TILE_WIDTH);                      // ld a, 4 * TILE_WIDTH
    // LD_addr_A(wVirtualOAMSprite38YCoord);      // ld [wVirtualOAMSprite38YCoord], a
    // LD_addr_A(wVirtualOAMSprite39YCoord);      // ld [wVirtualOAMSprite39YCoord], a
    // LD_A(10 * TILE_WIDTH);                     // ld a, 10 * TILE_WIDTH
    // LD_addr_A(wVirtualOAMSprite38XCoord);      // ld [wVirtualOAMSprite38XCoord], a
    // LD_A(11 * TILE_WIDTH);                     // ld a, 11 * TILE_WIDTH
    // LD_addr_A(wVirtualOAMSprite39XCoord);      // ld [wVirtualOAMSprite39XCoord], a
    // XOR_A_A;                                   // xor a
    // LD_addr_A(wVirtualOAMSprite38Attributes);  // ld [wVirtualOAMSprite38Attributes], a
    // LD_addr_A(wVirtualOAMSprite39Attributes);  // ld [wVirtualOAMSprite39Attributes], a
    // LD_A_addr(wUnusedBCDNumber);               // ld a, [wUnusedBCDNumber]
    // CP_A(100);                                 // cp 100
    // IF_NC goto max;                            // jr nc, .max
    // ADD_A(1);                                  // add 1
    // DAA;                                       // daa
    // LD_B_A;                                    // ld b, a
    // SWAP_A;                                    // swap a
    // AND_A(0xf);                                // and $f
    // ADD_A(0xf6);                               // add "0"
    // LD_addr_A(wVirtualOAMSprite38TileID);      // ld [wVirtualOAMSprite38TileID], a
    // LD_A_B;                                    // ld a, b
    // AND_A(0xf);                                // and $f
    // ADD_A(0xf6);                               // add "0"
    // LD_addr_A(wVirtualOAMSprite39TileID);      // ld [wVirtualOAMSprite39TileID], a
    // RET;                                       // ret

// max:
    // LD_A(0xff);                            // ld a, "9"
    // LD_addr_A(wVirtualOAMSprite38TileID);  // ld [wVirtualOAMSprite38TileID], a
    // LD_addr_A(wVirtualOAMSprite39TileID);  // ld [wVirtualOAMSprite39TileID], a
    // RET;                                   // ret
}

//  Return true if any SFX channels are active.
bool CheckSFX(void) {
    if (chan[CHAN5]->channelOn) return true;
    if (chan[CHAN6]->channelOn) return true;
    if (chan[CHAN7]->channelOn) return true;
    if (chan[CHAN8]->channelOn) return true;
    return false;
}

void TerminateExpBarSound(void) {
    // XOR_A_A;  // xor a
    chan[CHAN5]->flags[0] = 0;
    // LD_addr_A(wPitchSweep);  // ld [wPitchSweep], a
    wram->wPitchSweep = 0;
    // LDH_addr_A(rNR10);       // ldh [rNR10], a
    gb_write(rNR10, 0x0);
    // LDH_addr_A(rNR11);       // ldh [rNR11], a
    gb_write(rNR11, 0x0);
    // LDH_addr_A(rNR12);       // ldh [rNR12], a
    gb_write(rNR12, 0x0);
    // LDH_addr_A(rNR13);       // ldh [rNR13], a
    gb_write(rNR13, 0x0);
    // LDH_addr_A(rNR14);       // ldh [rNR14], a
    gb_write(rNR14, 0x0);
    // RET;                     // ret
}

// Quickly turn off music channels
void ChannelsOff(void) {
    chan[CHAN1]->channelOn = 0;
    chan[CHAN2]->channelOn = 0;
    chan[CHAN3]->channelOn = 0;
    chan[CHAN4]->channelOn = 0;
    wram->wPitchSweep = 0;
}

// Quickly turn off sound effect channels
void SFXChannelsOff(void) {
    chan[CHAN5]->channelOn = 0;
    chan[CHAN6]->channelOn = 0;
    chan[CHAN7]->channelOn = 0;
    chan[CHAN8]->channelOn = 0;
    wram->wPitchSweep = 0;
}
