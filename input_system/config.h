#pragma once
#include <stdbool.h>
#include "input.h"

bool config_load(const char* filename);
bool config_save(const char* filename);
void config_set_key_binding(const char* action, SDL_Scancode primary, SDL_Scancode secondary);
void config_set_mouse_button_binding(const char* action, Uint8 button);
