#include <stdarg.h>
#include <stdio.h>
#include "log.h"


static log_level_t s_loglevel = LOG_INFO;
static FILE *s_logdest = NULL;

struct Logger {
    log_level_t level;
    FILE* dest;
};

void log_set_level(log_level_t level) {
    s_loglevel = level;
}

void log_set_dest(FILE* f) {
    s_logdest = f;
}

void logger_set_level(struct Logger *l, log_level_t level) {
    l->level = level;
}

void logger_set_dest(struct Logger *l, FILE* f) {
    l->dest = f;
}

int log_msg_impl(log_level_t level, const char* file, int line, const char* fmt, ...) {
    int written = 0;
    if(s_loglevel == LOG_NONE || s_loglevel < level)
        return written;

    va_list v;
    va_start(v, fmt);
    FILE* f = (s_logdest)? s_logdest: stderr;
    switch(level)
    {
        default: break;
        case LOG_ERROR: written += fprintf(f, "[ERROR %s:%d]: ", file, line); break;
        case LOG_WARN: written += fprintf(f, "[WARN %s:%d]: ", file, line); break;
        case LOG_INFO: written += fprintf(f, "[INFO %s:%d]: ", file, line); break;
        case LOG_DEBUG: written += fprintf(f, "[DEBUG %s:%d]: ", file, line); break;
    }
    written += vfprintf(f, fmt, v);
    va_end(v);
    return written;
}

int loga_msg_impl(log_level_t level, const char* fmt, ...) {
    int written = 0;
    if(s_loglevel == LOG_NONE || s_loglevel < level)
        return written;

    va_list v;
    va_start(v, fmt);
    FILE* f = (s_logdest)? s_logdest: stderr;
    written += vfprintf(f, fmt, v);
    va_end(v);
    return written;
}
