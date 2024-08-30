#pragma once

#if defined(_MSC_VER)
#define noreturn __declspec(noreturn)
#else
#define noreturn __attribute__((noreturn))
#endif

enum {
    RESET_TYPE_START, // Cold boot
    RESET_TYPE_RESET, // Warm boot / reset
    RESET_TYPE_INIT = -1, // No call to Reset or Start
};

noreturn void SoftReset(int value);
