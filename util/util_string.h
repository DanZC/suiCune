#pragma once

uint8_t* Utf8ToCrystal(const char* src);
uint8_t* Utf8ToCrystalBuffer(uint8_t* dest, size_t dest_size, const char* src);
void CopyStringToGB(uint16_t dest, const char* src);
void CopyUTF8StringToGB(uint16_t dest, const char* src);
void CopyUTF8NStringToGB(uint16_t dest, uint16_t n, const char* src);
void CopyStringFromGB(uint8_t* dest, size_t dest_size, uint16_t src);
uint16_t PrintCrystalStringFromGB(uint16_t ptr);
void PrintCrystalTextFromGB(uint16_t ptr);

/// Convenience macros

// Converts UTF-8 encoded string to Crystal encoding.
// Returns address to temp buffer containing encoded string.
#define U82C(_s) Utf8ToCrystal(_s)

// Converts UTF-8 encoded string to Crystal encoding.
// Returns address to passed buffer containing encoded string.
#define U82CB(_d, _ds, _s) Utf8ToCrystalBuffer(_d, _ds, _s)

// Converts UTF-8 encoded string to Crystal encoding.
// Returns address to passed array containing encoded string.
#define U82CA(_d, _s) Utf8ToCrystalBuffer(_d, sizeof(_d), _s)