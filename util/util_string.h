#pragma once

uint8_t* Utf8ToCrystal(const char* src);
uint8_t* Utf8ToCrystalBuffer(uint8_t* dest, size_t dest_size, const char* src);
void CopyStringToGB(uint16_t dest, const char* src);
void CopyUTF8StringToGB(uint16_t dest, const char* src);
void CopyUTF8NStringToGB(uint16_t dest, uint16_t n, const char* src);
void CopyStringFromGB(uint8_t* dest, size_t dest_size, uint16_t src);
uint16_t PrintCrystalStringFromGB(uint16_t ptr);
void PrintCrystalTextFromGB(uint16_t ptr);