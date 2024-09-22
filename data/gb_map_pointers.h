#pragma once

void PopulateMapPointerTable(void);
uint32_t GetGBMapAttributePointer(uint8_t group, uint8_t map);
uint32_t GetGBMapBlocksPointer(uint8_t group, uint8_t map);
uint32_t GetGBMapScriptsPointer(uint8_t group, uint8_t map);
uint32_t GetGBMapEventsPointer(uint8_t group, uint8_t map);
