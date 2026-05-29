static int s_debug_mode = 0;

void debug_mode_set(int enabled) {
    s_debug_mode = enabled;
}

void debug_mode_set_default(void) {
#if DEBUG
    s_debug_mode = 1;
#else
    s_debug_mode = 0;
#endif
}

int debug_mode(void) {
    return s_debug_mode;
}
