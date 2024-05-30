#pragma once

#if defined(_MSC_VER)
#define noreturn __declspec(noreturn)
#else
#define noreturn __attribute__((noreturn))
#endif

noreturn void SoftReset(int value);
