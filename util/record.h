#ifdef _MSC_VER
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif // _MSVC_VER
#include <stdbool.h>

void TakeScreenshot(const char* path);

void StartRecording(const char* dest, const char* dir);
void RecordFrame(void);
void StopAndSaveRecording(void);
void StopAndDiscardRecording(void);
