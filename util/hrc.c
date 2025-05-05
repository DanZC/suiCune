#include "enhancements.h"
#if !ENHANCEMENT_USE_PCG
#include <stdint.h>
#include <stdio.h>
#include "./hrc.h"
/// Convert seconds to nanoseconds
#define SEC_TO_NS(sec) ((sec)*1000000000)

#if defined(__unix__)
#include <errno.h>  // `errno`
#include <string.h> // `strerror(errno)`
#include <time.h>   // `clock_gettime()` and `timespec_get()`

uint64_t GetNanoseconds(void){
    uint64_t nanoseconds;
    struct timespec ts;
    int return_code = clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    if (return_code == -1)
    {
        printf("Failed to obtain timestamp. errno = %i: %s\n", errno, 
            strerror(errno));
        nanoseconds = UINT64_MAX; // use this to indicate error
    }
    else
    {
        // `ts` now contains your timestamp in seconds and nanoseconds! To 
        // convert the whole struct to nanoseconds, do this:
        nanoseconds = SEC_TO_NS((uint64_t)ts.tv_sec) + (uint64_t)ts.tv_nsec;
    }
    return nanoseconds;
}
#elif defined(_WIN32)
#include <windows.h>

uint64_t GetNanoseconds(void){
    LARGE_INTEGER ticks;
    LARGE_INTEGER freq;
    if (!QueryPerformanceCounter(&ticks))
    {
        printf("Failed to obtain timestamp.\n");
        return UINT64_MAX; // use this to indicate error
    }
    if (!QueryPerformanceFrequency(&freq))
    {
        printf("Failed to obtain frequency.\n");
        return UINT64_MAX; // use this to indicate error
    }
    return (uint64_t)(SEC_TO_NS((double)ticks.QuadPart / (double)freq.QuadPart));
}
#else
#error "Unsupported platform?"
#endif
#endif
