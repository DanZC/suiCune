#pragma once
// We'll need to define structs or types to represent things like menus
typedef struct {
    int id;
    const char* name;
    void (*handler)(void);
} MenuOption;