#include <SDL2/SDL.h>

#include <stdbool.h>
#include <string.h>
#include "json.h"
#include "log.h"
#include "../constants.h"
#include "uthash.h"
#include "../data/constant_strings.h"
#include "record.h"
#include "input.h"

typedef enum {
    GAME_INPUT_A,
    GAME_INPUT_B,
    GAME_INPUT_START,
    GAME_INPUT_SELECT,
    GAME_INPUT_D_UP,
    GAME_INPUT_D_DOWN,
    GAME_INPUT_D_LEFT,
    GAME_INPUT_D_RIGHT,
    GAME_INPUT_SCREENSHOT,
    GAME_INPUT_RECORD,
} game_input_e;

#define STRINGIFY(e) [e] = #e

const char* game_input_e_strings[] = {
    STRINGIFY(GAME_INPUT_A),
    STRINGIFY(GAME_INPUT_B),
    STRINGIFY(GAME_INPUT_START),
    STRINGIFY(GAME_INPUT_SELECT),
    STRINGIFY(GAME_INPUT_D_UP),
    STRINGIFY(GAME_INPUT_D_DOWN),
    STRINGIFY(GAME_INPUT_D_LEFT),
    STRINGIFY(GAME_INPUT_D_RIGHT),
    STRINGIFY(GAME_INPUT_SCREENSHOT),
    STRINGIFY(GAME_INPUT_RECORD),
};

typedef union {
    struct
    {
        uint8_t a : 1;
        uint8_t b : 1;
        uint8_t select : 1;
        uint8_t start : 1;
        uint8_t right : 1;
        uint8_t left : 1;
        uint8_t up : 1;
        uint8_t down : 1;
    } joypad_bits;
    uint8_t joypad;
} joypad_bits_t;

typedef struct {
    SDL_Scancode key;
    game_input_e game_input;
    UT_hash_handle hh;
} key_input;
key_input *key_input_mappings = NULL;

static void add_key_binding(SDL_Scancode key, game_input_e game_input) {
    key_input* item = malloc(sizeof(*item));
    item->key = key;
    item->game_input = game_input;
    HASH_ADD_INT(key_input_mappings,key, item);
}

typedef struct ControllerButtonInput {
    SDL_GameControllerButton button;
    game_input_e game_input;
    UT_hash_handle hh;
} button_input;
button_input *button_input_mappings = NULL;

static void add_controller_button_binding(SDL_GameControllerButton button, game_input_e game_input) {
    button_input* item = malloc(sizeof(*item));
    item->button = button;
    item->game_input = game_input;
    HASH_ADD_INT(button_input_mappings,button, item);
}

static key_input* input_get_key(SDL_Scancode key) {
    key_input* item;
    HASH_FIND_INT(key_input_mappings, &key, item);
    return item;
}

static button_input* input_get_controller_button(SDL_GameControllerButton button) {
    button_input* item;
    HASH_FIND_INT(button_input_mappings, &button, item);
    return item;
}

game_input_e get_input_from_string(const char* string, size_t size) {
    for(size_t i = 0; i < lengthof(game_input_e_strings); ++i) {
        if(strncmp(game_input_e_strings[i], string, size) == 0)
            return i;
    }
    return (game_input_e)-1;
}

bool load_input_mapping(void) {
    FILE *f = fopen("bindings.json", "r");
    bool result = false;
    if(!f) {
        log_info("bindings.json not found. Creating default mappings...\n");
        f = fopen("bindings.json", "w");
        if(!f) {
            log_err("Could not create bindings.json.\n");
            return false;
        }
        fprintf(f, "%s\n",
"{\n"
"    \"keyboard\": {\n"
"        \"SDL_SCANCODE_W\": \"GAME_INPUT_D_UP\",\n"
"        \"SDL_SCANCODE_UP\": \"GAME_INPUT_D_UP\",\n"
"        \"SDL_SCANCODE_A\": \"GAME_INPUT_D_LEFT\",\n"
"        \"SDL_SCANCODE_LEFT\": \"GAME_INPUT_D_LEFT\",\n"
"        \"SDL_SCANCODE_S\": \"GAME_INPUT_D_DOWN\",\n"
"        \"SDL_SCANCODE_DOWN\": \"GAME_INPUT_D_DOWN\",\n"
"        \"SDL_SCANCODE_D\": \"GAME_INPUT_D_RIGHT\",\n"
"        \"SDL_SCANCODE_RIGHT\": \"GAME_INPUT_D_RIGHT\",\n"
"        \"SDL_SCANCODE_Z\": \"GAME_INPUT_A\",\n"
"        \"SDL_SCANCODE_X\": \"GAME_INPUT_B\",\n"
"        \"SDL_SCANCODE_RETURN\": \"GAME_INPUT_START\",\n"
"        \"SDL_SCANCODE_BACKSPACE\": \"GAME_INPUT_SELECT\"\n"
"    },\n"
"    \"controller\": {\n"
"        \"SDL_CONTROLLER_BUTTON_A\": \"GAME_INPUT_A\",\n"
"        \"SDL_CONTROLLER_BUTTON_B\": \"GAME_INPUT_B\",\n"
"        \"SDL_CONTROLLER_BUTTON_START\": \"GAME_INPUT_START\",\n"
"        \"SDL_CONTROLLER_BUTTON_BACK\": \"GAME_INPUT_SELECT\",\n"
"        \"SDL_CONTROLLER_BUTTON_DPAD_UP\": \"GAME_INPUT_D_UP\",\n"
"        \"SDL_CONTROLLER_BUTTON_DPAD_DOWN\": \"GAME_INPUT_D_DOWN\",\n"
"        \"SDL_CONTROLLER_BUTTON_DPAD_LEFT\": \"GAME_INPUT_D_LEFT\",\n"
"        \"SDL_CONTROLLER_BUTTON_DPAD_RIGHT\": \"GAME_INPUT_D_RIGHT\"\n"
"    }\n"
"}");
        fclose(f);
        f = fopen("bindings.json", "r");
        if(!f) {
            log_err("Could not open bindings.json.\n");
            return false;
        }
    }
    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);
    fseek(f, 0, SEEK_SET);
    uint8_t* data = malloc(size + 1);
    size_t read = fread(data, 1, size, f);
    fclose(f);
    data[read] = '\0';
    json_value_t* root = json_parse(data, read);
    if(!root) {
        goto exit;
    }

    json_object_t* root_obj = json_value_as_object(root);
    if(!root_obj) {
        goto exit2;
    }

    for(json_object_element_t* root_it = root_obj->start; root_it != NULL; root_it = root_it->next) {
        if(strcmp(root_it->name->string, "keyboard") == 0) {
            json_object_t* keyboard_bindings = json_value_as_object(root_it->value);
            if(!keyboard_bindings)
                continue;
            for(json_object_element_t* it = keyboard_bindings->start; it != NULL; it = it->next) {
                const char* key = it->name->string;
                u32_flag_s res = FindConstantValueByString(key);
                if(!res.flag) {
                    log_warn("%s is not a valid name for an input. Skipping.\n", key);
                    continue;
                }
                SDL_Scancode code = (SDL_Scancode)res.a;
                json_value_t* value = it->value;
                json_string_t* value_str = json_value_as_string(value);
                if(!value_str) {
                    log_warn("Mapped value for %s is not a string. Skipping.\n", key);
                    continue;
                }
                game_input_e input = get_input_from_string(value_str->string, value_str->string_size);
                if(input == (game_input_e)-1) {
                    log_warn("Mapped value %.*s for %s is not a valid game input constant. Skipping.\n",
                            value_str->string_size, value_str->string, key);
                    continue;
                }
                add_key_binding(code, input);
            }
        }
        if(strcmp(root_it->name->string, "controller") == 0) {
            json_object_t* controller_bindings = json_value_as_object(root_it->value);
            if(!controller_bindings)
                continue;
            for(json_object_element_t* it = controller_bindings->start; it != NULL; it = it->next) {
                const char* key = it->name->string;
                u32_flag_s res = FindConstantValueByString(key);
                if(!res.flag) {
                    log_warn("%s is not a valid name for an input. Skipping.\n", key);
                    continue;
                }
                SDL_GameControllerButton code = (SDL_GameControllerButton)res.a;
                json_value_t* value = it->value;
                json_string_t* value_str = json_value_as_string(value);
                if(!value_str) {
                    log_warn("Mapped value for %s is not a string. Skipping.\n", key);
                    continue;
                }
                game_input_e input = get_input_from_string(value_str->string, value_str->string_size);
                if(input == (game_input_e)-1) {
                    log_warn("Mapped value %.*s for %s is not a valid game input constant. Skipping.\n",
                            value_str->string_size, value_str->string, key);
                    continue;
                }
                add_controller_button_binding(code, input);
            }
        }
    }

    result = true;
exit2:
    free(root);
exit:
    free(data);
    return result;
}

void init_input_mapping(void) {
    if(load_input_mapping()) {
        log_info("Loaded input mapping from bindings.json\n");
        return;
    }

    log_warn("Could not load input mapping from bindings.json. Loading default mapping.\n");

    add_key_binding(SDL_SCANCODE_UP, GAME_INPUT_D_UP);
    add_key_binding(SDL_SCANCODE_DOWN, GAME_INPUT_D_DOWN);
    add_key_binding(SDL_SCANCODE_LEFT, GAME_INPUT_D_LEFT);
    add_key_binding(SDL_SCANCODE_RIGHT, GAME_INPUT_D_RIGHT);
    add_key_binding(SDL_SCANCODE_W, GAME_INPUT_D_UP);
    add_key_binding(SDL_SCANCODE_S, GAME_INPUT_D_DOWN);
    add_key_binding(SDL_SCANCODE_A, GAME_INPUT_D_LEFT);
    add_key_binding(SDL_SCANCODE_D, GAME_INPUT_D_RIGHT);
    add_key_binding(SDL_SCANCODE_Z, GAME_INPUT_A);
    add_key_binding(SDL_SCANCODE_X, GAME_INPUT_B);
    add_key_binding(SDL_SCANCODE_RETURN, GAME_INPUT_START);
    add_key_binding(SDL_SCANCODE_BACKSPACE, GAME_INPUT_SELECT);

    add_controller_button_binding(SDL_CONTROLLER_BUTTON_A, GAME_INPUT_A);
    add_controller_button_binding(SDL_CONTROLLER_BUTTON_B, GAME_INPUT_B);
    add_controller_button_binding(SDL_CONTROLLER_BUTTON_START, GAME_INPUT_START);
    add_controller_button_binding(SDL_CONTROLLER_BUTTON_BACK, GAME_INPUT_SELECT);
    add_controller_button_binding(SDL_CONTROLLER_BUTTON_DPAD_UP, GAME_INPUT_D_UP);
    add_controller_button_binding(SDL_CONTROLLER_BUTTON_DPAD_DOWN, GAME_INPUT_D_DOWN);
    add_controller_button_binding(SDL_CONTROLLER_BUTTON_DPAD_LEFT, GAME_INPUT_D_LEFT);
    add_controller_button_binding(SDL_CONTROLLER_BUTTON_DPAD_RIGHT, GAME_INPUT_D_RIGHT);
}

void handle_input(game_input_e input, bool up, joypad_bits_t* jp) {
    switch(input) {
        case GAME_INPUT_A:      jp->joypad_bits.a = up; break;
        case GAME_INPUT_B:      jp->joypad_bits.b = up; break;
        case GAME_INPUT_START:  jp->joypad_bits.start = up; break;
        case GAME_INPUT_SELECT: jp->joypad_bits.select = up; break;
        case GAME_INPUT_D_DOWN: jp->joypad_bits.down = up; break;
        case GAME_INPUT_D_LEFT: jp->joypad_bits.left = up; break;
        case GAME_INPUT_D_RIGHT: jp->joypad_bits.right = up; break;
        case GAME_INPUT_D_UP:   jp->joypad_bits.up = up; break;
        case GAME_INPUT_SCREENSHOT: {
            if(up)
                return;
            TakeScreenshot(NULL);
        } return;
        case GAME_INPUT_RECORD:
            if(!up) StartRecording(NULL, NULL);
    }
}

void handle_input_key(const SDL_KeyboardEvent* e, joypad_bits_t* jp) {
    key_input* k = input_get_key(e->keysym.scancode);
    if(!k)
        return;
    bool up = e->state == SDL_RELEASED ? true : false;
    return handle_input(k->game_input, up, jp);
}

void handle_input_button(const SDL_ControllerButtonEvent* e, joypad_bits_t* jp) {
    button_input* b = input_get_controller_button(e->button);
    if(!b)
        return;
    bool up = e->state == SDL_RELEASED ? true : false;
    return handle_input(b->game_input, up, jp);
}

void handle_input_event(const SDL_Event* e, uint8_t* jp) {
    switch(e->type) {
        case SDL_KEYUP:
        case SDL_KEYDOWN:
            return handle_input_key(&e->key, (joypad_bits_t*)jp);
        case SDL_CONTROLLERBUTTONDOWN:
        case SDL_CONTROLLERBUTTONUP:
            return handle_input_button(&e->cbutton, (joypad_bits_t*)jp);
    }
}

