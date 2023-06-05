#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "uthash.h"

typedef enum input_state {
    NONE,
    PRESSED,
    RELEASED,
    HELD
} input_state;

typedef struct key_input {
    SDL_Scancode key[2];
    input_state state;
    float frames;
} key_input;

typedef struct mouse_button_input {
    Uint8 button;
    input_state state;
    float frames;
} mouse_button_input;

typedef struct ivector2 {
    int x, y;
} ivector2;

void input_init(void);
void input_update(void);
void input_register_key(const char* key, SDL_Scancode primary, SDL_Scancode secondary);
void input_register_mouse_button(const char* button, Uint8 sdl_button);
key_input* input_get_key(const char* key);
mouse_button_input* input_get_mouse_button(const char* button);
ivector2 input_get_cursor_pos(void);
int input_get_scroll_wheel(void);
void input_set_considered_held(float value);

typedef struct key_map_item {
    const char* key;
    key_input value;
    UT_hash_handle hh;
} key_map_item;

typedef struct mouse_button_map_item {
    const char* key;
    mouse_button_input value;
    UT_hash_handle hh;
} mouse_button_map_item;

key_map_item* input_get_key_map(const char* key);
mouse_button_map_item* input_get_mouse_button_map(const char* key);

key_map_item* input_get_first_key_item(void);
mouse_button_map_item* input_get_first_mouse_button_item(void);

#endif // INPUT_H