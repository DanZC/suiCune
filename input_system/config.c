#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "config.h"
#include "default_config.h"
#include "ini.h"
#include "input.h"

static int config_handler(void* user, const char* section, const char* name, const char* value) {
    if (strcmp(section, "keys") == 0) {
        SDL_Scancode primary, secondary;
        sscanf(value, "%d %d", &primary, &secondary);
        input_register_key(name, primary, secondary);
    }
    else if (strcmp(section, "mouse") == 0) {
        Uint8 button;
        sscanf(value, "%hhu", &button);
        input_register_mouse_button(name, button);
    }
    return 1;
}

bool config_load(const char* filename) {
    struct stat buffer;
    if (stat(filename, &buffer) != 0) {
        // If the file does not exist, create it with the default contents
        FILE* file = fopen(filename, "w");
        if (file) {
            fputs(DEFAULT_CONFIG, file);
            fclose(file);
        }
    }

    return ini_parse(filename, config_handler, NULL) == 0;
}

bool config_save(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        return false;
    }

    fputs("[keys]\n", file);
    key_map_item* key_item;
    for (key_item = input_get_first_key_item(); key_item != NULL; key_item = (key_map_item*)(key_item->hh.next)) {
        fprintf(file, "%s=%d %d\n", key_item->key, key_item->value.key[0], key_item->value.key[1]);
    }

    fputs("\n[mouse]\n", file);
    mouse_button_map_item* mouse_item;
    for (mouse_item = input_get_first_mouse_button_item(); mouse_item != NULL; mouse_item = (mouse_button_map_item*)(mouse_item->hh.next)) {
        fprintf(file, "%s=%hhu\n", mouse_item->key, mouse_item->value.button);
    }

    fclose(file);
    return true;
}

void config_set_key_binding(const char* action, SDL_Scancode primary, SDL_Scancode secondary) {
    key_input* key = input_get_key(action);
    if (key) {
        key->key[0] = primary;
        key->key[1] = secondary;
    }
}

void config_set_mouse_button_binding(const char* action, Uint8 button) {
    mouse_button_input* mouse_button = input_get_mouse_button(action);
    if (mouse_button) {
        mouse_button->button = button;
    }
}
