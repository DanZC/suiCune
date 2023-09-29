#include <SDL2/SDL.h>
#include <stdbool.h>

void TakeScreenshot(const char* path);

void StartRecording(const char* dest, const char* dir);
void RecordFrame(void);
void StopAndSaveRecording(void);
void StopAndDiscardRecording(void);
