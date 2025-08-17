#ifndef RUNTIMELOGGER_LOG_H
#define RUNTIMELOGGER_LOG_H
#include <time.h>

typedef enum {
  LOG_RuntimeLogger_mode_default,
  LOG_RuntimeLogger_mode_silent,
} LOG_RuntimeLogger_mode;

typedef enum {
  LOG_RuntimeLogger_code_null = 0,
  LOG_RuntimeLogger_code_error = 1,
  LOG_RuntimeLogger_code_success = 2,
  LOG_RuntimeLogger_code_warning = 3,
  LOG_RuntimeLogger_code_info = 4,
} LOG_RuntimeLogger_code;

extern LOG_RuntimeLogger_mode runtimeLogger_mode;

int LOG_runtimeLogger_log(const char *message, LOG_RuntimeLogger_code code,
                      const char *file, int line);

typedef struct {
  time_t timestamp;
  int code;
  const char *message;
  const char *file;
  int line;
} LOG_Log;

void LOG_runtimeLogger_reset(void);
LOG_Log LOG_runtimeLogger_get_last_log(void);

#define LOG_ERROR(description)                                                 \
  LOG_runtimeLogger_log(description, LOG_RuntimeLogger_code_error, __FILE__, __LINE__)

#define LOG_WARNING(description)                                               \
  LOG_runtimeLogger_log(description, LOG_RuntimeLogger_code_warning, __FILE__, __LINE__)

#define LOG_INFO(description)                                                  \
  LOG_runtimeLogger_log(description, LOG_RuntimeLogger_code_info, __FILE__, __LINE__)

#define LOG_SUCCESS(description)                                                  \
  LOG_runtimeLogger_log(description, LOG_RuntimeLogger_code_success, __FILE__, __LINE__)
#endif
