#pragma once

void Printer_Begin(void);
void Printer_AppendTilemap(const uint8_t* tilemap, const uint8_t* attrmap, uint8_t h);
void Printer_SaveToDisk(void);
void Printer_CleanUp(void);
