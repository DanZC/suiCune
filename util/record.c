#include <stdio.h>
#include <time.h>
#include "../tools/emu/peanut_gb.h"
#include <stdlib.h>
#include "record.h"
#include <memory.h>

#define FFMPEG_PROG "D:/ffmpeg/bin/ffmpeg.exe"

#define MAX_FRAMES (60 * 60) // 60 seconds of video

#ifdef _MSC_VER
#ifndef PATH_MAX
#define PATH_MAX 260
#endif
#endif

struct priv_t {
    /* Pointer to allocated memory holding GB file. */
    uint8_t *rom;
    /* Pointer to allocated memory holding save file. */
    uint8_t *cart_ram;

    /* Colour palette for each BG, OBJ0, and OBJ1. */
    uint16_t selected_palette[3][4];
    uint16_t fb[LCD_HEIGHT][LCD_WIDTH];
};

extern struct gb_s gb;

void TakeScreenshot(const char* path) {
    uint16_t (*pix)[LCD_WIDTH] = ((struct priv_t*)gb.direct.priv)->fb;
    SDL_Surface* surf = SDL_CreateRGBSurfaceWithFormatFrom(pix, LCD_WIDTH, LCD_HEIGHT, 16, 2 * LCD_WIDTH, SDL_PIXELFORMAT_RGB555);
    char name[128];
    if(!surf) {
        fprintf(stderr, "SDL error: %s\n", SDL_GetError());
        exit(-1);
    }
    if(path == NULL) {
        time_t now = time(NULL);
        struct tm nowt;
        localtime_s(&nowt, &now);
        strftime(name, sizeof(name), "./screenshot%Y_%m_%d_T%H_%M_%S.bmp", &nowt);
        SDL_SaveBMP(surf, name);
        path = name;
    }
    else {
        SDL_SaveBMP(surf, path);
    }
    SDL_FreeSurface(surf);
    printf("Saved screenshot to \"%s\".\n", path);
}

static void GenerateMP4(const char* in_dir, const char* out) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), FFMPEG_PROG " -framerate 60 -pattern_type sequence -i \"%s/frame%%08d.bmp\" -c:v libx264 -pix_fmt yuv420p %s", in_dir, out);
    printf("%s\n", cmd);
    int error = system(cmd);
    if(error == EXIT_SUCCESS) {
        printf("Wrote recording to %s.\n", out);
    }
    else {
        fprintf(stderr, "cmd error: %d\n", error);
    }
}

static void DeleteDir(const char* in_dir) {
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "rm -rf %s", in_dir);
    printf("%s\n", cmd);
    system(cmd);
}

static void CreateDir(const char* in_dir) {
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "mkdir \"%s\"", in_dir);
    printf("%s\n", cmd);
    system(cmd);
}

struct VideoBuffer {
    uint8_t (*frames)[LCD_WIDTH * LCD_HEIGHT * 2];
    size_t frame_count;
    size_t capacity;
};

void BufferFrame(struct VideoBuffer* vb) {
    uint16_t (*pix)[LCD_WIDTH] = ((struct priv_t*)gb.direct.priv)->fb;
    memcpy(vb->frames + vb->frame_count, pix, sizeof(*vb->frames));
    vb->frame_count++;
}

struct RecordingData {
    bool recording;
    struct VideoBuffer buffer;
    char dest[PATH_MAX + 1];
    char dir[PATH_MAX + 1];
} gRecording;

void StartRecording(const char* dest, const char* dir) {
    if(gRecording.recording)
        StopAndSaveRecording();
    gRecording.recording = true;
    if(dest == NULL) {
        time_t now = time(NULL);
        struct tm nowt;
        localtime_s(&nowt, &now);
        strftime(gRecording.dest, sizeof(gRecording.dest), "./recording%Y_%m_%d_T%H_%M_%S.mp4", &nowt);
    } else {
        strcpy(gRecording.dest, dest);
    }
    if(dir == NULL) {
        strcpy(gRecording.dir, "./temp");
    }
    else {
        strcpy(gRecording.dir, dir);
    }
    CreateDir(gRecording.dir);
    gRecording.buffer.frames = malloc(sizeof(gRecording.buffer.frames[0]) * 64);
    gRecording.buffer.frame_count = 0;
    gRecording.buffer.capacity = 16;
    printf("Started recording to %s.\n", gRecording.dest);
}

void RecordFrame(void) {
    if(!gRecording.recording)
        return;
    if(gRecording.buffer.frame_count == MAX_FRAMES) {
        return StopAndSaveRecording();
    }
    if(gRecording.buffer.frame_count == gRecording.buffer.capacity) {
        printf("Resizing buffer to %lld frames...\n", ((gRecording.buffer.capacity * 3) / 2));
        void* new_buf = realloc(gRecording.buffer.frames, sizeof(gRecording.buffer.frames[0]) * ((gRecording.buffer.capacity * 3) / 2));
        if(new_buf) {
            gRecording.buffer.capacity = (gRecording.buffer.capacity * 3) / 2;
            gRecording.buffer.frames = new_buf;
        }
        else {
            fprintf(stderr, "Out of memory.\n");
            return StopAndDiscardRecording();
        }
    }
    BufferFrame(&gRecording.buffer);
}

void StopAndSaveRecording(void) {
    if(!gRecording.recording)
        return;
    gRecording.recording = false;
    printf("Stopping recording...\n");
    for(size_t i = 0; i < gRecording.buffer.frame_count; i++) {
        char dest[FILENAME_MAX * 2];
        sprintf(dest, "%s/frame%08lld.bmp", gRecording.dir, i);
        SDL_Surface* surf = SDL_CreateRGBSurfaceWithFormatFrom(gRecording.buffer.frames[i], LCD_WIDTH, LCD_HEIGHT, 16, LCD_WIDTH * 2, SDL_PIXELFORMAT_RGB555);
        SDL_SaveBMP(surf, dest);
        SDL_FreeSurface(surf);
    }
    free(gRecording.buffer.frames);
    gRecording.buffer.frames = NULL;
    GenerateMP4(gRecording.dir, gRecording.dest);
    DeleteDir(gRecording.dir);
}

void StopAndDiscardRecording(void) {
    gRecording.recording = false;
    free(gRecording.buffer.frames);
    gRecording.buffer.frames = NULL;
    gRecording.buffer.frame_count = 0;
    gRecording.buffer.capacity = 0;
    DeleteDir(gRecording.dir);
}