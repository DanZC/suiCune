#pragma once

typedef enum {
    LOG_NONE,
    LOG_ERROR,
    LOG_WARN,
    LOG_INFO,
    LOG_DEBUG,
} log_level_t;

void log_set_level(log_level_t level);
void log_set_dest(FILE* f);

log_level_t log_get_level(void);

int log_msg_impl(log_level_t level, const char* file, int line, const char* fmt, ...);
int loga_msg_impl(log_level_t level, const char* fmt, ...);

#define log_msg(level, fmt, ...) log_msg_impl(level, __func__, __LINE__, fmt, ##__VA_ARGS__)
#define log_err(fmt, ...) log_msg(LOG_ERROR, fmt, ##__VA_ARGS__)
#define log_warn(fmt, ...) log_msg(LOG_WARN, fmt, ##__VA_ARGS__)
#define log_info(fmt, ...) log_msg(LOG_INFO, fmt, ##__VA_ARGS__)
#define log_debug(fmt, ...) log_msg(LOG_DEBUG, fmt, ##__VA_ARGS__)

#define loga_msg(level, fmt, ...) loga_msg_impl(level, fmt, ##__VA_ARGS__)
#define loga_err(fmt, ...) loga_msg(LOG_ERROR, fmt, ##__VA_ARGS__)
#define loga_warn(fmt, ...) loga_msg(LOG_WARN, fmt, ##__VA_ARGS__)
#define loga_info(fmt, ...) loga_msg(LOG_INFO, fmt, ##__VA_ARGS__)
#define loga_debug(fmt, ...) loga_msg(LOG_DEBUG, fmt, ##__VA_ARGS__)

