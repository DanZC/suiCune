#include "input.h"
#include <SDL2/SDL_events.h>
#include <string.h>
#include <SDL_scancode.h>
#include "uthash.h"

key_map_item* keys = NULL;
mouse_button_map_item* mouse_buttons = NULL;
ivector2 cursor_pos;
int scroll_wheel = 0;
float CONSIDERED_HELD = 0.5f;

void input_register_key(const char* key, SDL_Scancode primary, SDL_Scancode secondary) {
    key_input object = { { primary, secondary }, NONE, 0.0f };
    key_map_item* item = malloc(sizeof(key_map_item));
    item->key = key;
    item->value = object;
    HASH_ADD_KEYPTR(hh, keys, item->key, strlen(item->key), item);
}

void input_register_mouse_button(const char* button, Uint8 sdl_button) {
    mouse_button_input object = { sdl_button, NONE, 0.0f };
    mouse_button_map_item* item = malloc(sizeof(mouse_button_map_item));
    item->key = button;
    item->value = object;
    HASH_ADD_KEYPTR(hh, mouse_buttons, item->key, strlen(item->key), item);
}

key_input* input_get_key(const char* key) {
    key_map_item* item;
    HASH_FIND_STR(keys, key, item);
    return item ? &item->value : NULL;
}

mouse_button_input* input_get_mouse_button(const char* button) {
    mouse_button_map_item* item;
    HASH_FIND_STR(mouse_buttons, button, item);
    return item ? &item->value : NULL;
}

ivector2 input_get_cursor_pos() {
    return cursor_pos;
}

int input_get_scroll_wheel() {
    return scroll_wheel;
}

void input_set_considered_held(float value) {
    CONSIDERED_HELD = value;
}

key_map_item* input_get_key_map(const char* key) {
    key_map_item* item;
    HASH_FIND_STR(keys, key, item);
    return item;
}

mouse_button_map_item* input_get_mouse_button_map(const char* key) {
    mouse_button_map_item* item;
    HASH_FIND_STR(mouse_buttons, key, item);
    return item;
}

key_map_item* input_get_first_key_item() {
    return keys;
}

mouse_button_map_item* input_get_first_mouse_button_item() {
    return mouse_buttons;
}

static void input_update_key_state(key_map_item* item, bool down) {
    key_input* key = &item->value;
    if (down) {
        if (key->state == NONE) {
            key->state = PRESSED;
            key->frames = 0;
        }
        else if (key->state == PRESSED && key->frames >= CONSIDERED_HELD) {
            key->state = HELD;
        }
    }
    else {
        if (key->state == PRESSED || key->state == HELD) {
            key->state = RELEASED;
            key->frames = 0;
        }
        else if (key->state == RELEASED) {
            key->state = NONE;
        }
    }
}

static void input_update_mouse_button_state(mouse_button_map_item* item, bool down) {
    mouse_button_input* button = &item->value;
    if (down) {
        if (button->state == NONE) {
            button->state = PRESSED;
            button->frames = 0;
        }
        else if (button->state == PRESSED && button->frames >= CONSIDERED_HELD) {
            button->state = HELD;
        }
    }
    else {
        if (button->state == PRESSED || button->state == HELD) {
            button->state = RELEASED;
            button->frames = 0;
        }
        else if (button->state == RELEASED) {
            button->state = NONE;
        }
    }
}

void input_init(void) {
    memset(&cursor_pos, 0, sizeof(cursor_pos));
    scroll_wheel = 0;
}

void input_update(void) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            // Handle SDL_QUIT event
            break;
        case SDL_KEYDOWN:
        case SDL_KEYUP: {
            bool down = event.type == SDL_KEYDOWN;
            key_map_item* item;
            for (item = keys; item != NULL; item = (key_map_item*)(item->hh.next)) {
                if (item->value.key[0] == event.key.keysym.scancode || item->value.key[1] == event.key.keysym.scancode) {
                    input_update_key_state(item, down);
                    break;
                }
            }
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP: {
            bool down = event.type == SDL_MOUSEBUTTONDOWN;
            mouse_button_map_item* item;
            for (item = mouse_buttons; item != NULL; item = (mouse_button_map_item*)(item->hh.next)) {
                if (item->value.button == event.button.button) {
                    input_update_mouse_button_state(item, down);
                    break;
                }
            }
            break;
        }
        case SDL_MOUSEMOTION:
            cursor_pos.x = event.motion.x;
            cursor_pos.y = event.motion.y;
            break;
        case SDL_MOUSEWHEEL:
            scroll_wheel += event.wheel.y;
            break;
        default:
            break;
        }
    }

    key_map_item* key_item;
    for (key_item = keys; key_item != NULL; key_item = (key_map_item*)(key_item->hh.next)) {
        if (key_item->value.state == PRESSED || key_item->value.state == HELD || key_item->value.state == RELEASED) {
            key_item->value.frames += 1.0f / 60.0f; // Assuming 60fps
        }
    }

    mouse_button_map_item* mouse_item;
    for (mouse_item = mouse_buttons; mouse_item != NULL; mouse_item = (mouse_button_map_item*)(mouse_item->hh.next)) {
        if (mouse_item->value.state == PRESSED || mouse_item->value.state == HELD || mouse_item->value.state == RELEASED) {
            mouse_item->value.frames += 1.0f / 60.0f; // Assuming 60fps
        }
    }
}
