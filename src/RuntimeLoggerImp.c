#include "RuntimeLogger.h"
#include <stdio.h>
#include <time.h>

static char *colors[] = {
  "\x1b[30m",
  "\x1b[31m",
  "\x1b[32m",
  "\x1b[33m",
  "\x1b[34m",
  "\x1b[35m",
  "\x1b[36m",
  "\x1b[37m",
  "\x1b[0m",
};

typedef enum {
  Black,
  Red,
  Green,
  Yellow,
  Blue,
  Magenta,
  Cyan,
  White,
  Reset,
} Keys;

// Background Color:
// \x1b[40m - Black
// \x1b[42m - Green
// \x1b[43m - Yellow
// \x1b[44m - Blue
// \x1b[45m - Magenta
// \x1b[46m - Cyan
// \x1b[47m - White

// Text Attributes:
// \x1b[1m - Bold
// \x1b[4m - Underline
// \x1b[5m - Blink
// \x1b[7m - Invert colors (swap foreground and background)

static char *_$timestamp_to_string(time_t timestamp);

#define KEY(index) \
({ \
  char* _key = colors[index]; \
  _key; \
})

char *filename = "log.txt";
static LOG_Log log = (LOG_Log){.timestamp = 0, .message = "No error", .code = 0, .file = 0, .line = 0};
LOG_RuntimeLogger_mode runtimeLogger_mode = LOG_RuntimeLogger_mode_default;

void LOG_runtimeLogger_reset(void) {
  log = (LOG_Log){.timestamp = 0, .message = "no log...", .code = 0, .file = 0, .line = 0};
}

LOG_Log LOG_runtimeLogger_get_last_log(void) { return log; }

int LOG_runtimeLogger_log(const char *m, LOG_RuntimeLogger_code p, const char *f, int l) {
  time_t t;
  time(&t);
  static char buffer[256];
  char* start = KEY(p);
  char* end = KEY(Reset);
  char* date = _$timestamp_to_string(t);

  sprintf(buffer, "%s:%d; %s; %s", f,l, m, date);
  if(runtimeLogger_mode == LOG_RuntimeLogger_mode_default){
    printf("%s%s%s\n",start,buffer,end);
  }
  log = (LOG_Log){.timestamp = t,.message = m, .code = p, .file = f, .line = l};
  
  FILE *file = fopen(filename, "a");
  if (file == NULL) {
    perror("Failed to open log file");
    return p;
  }
  fprintf(file, "%s\n", buffer); 
  fclose(file);
  return p;
}

static char *_$timestamp_to_string(time_t timestamp) {
  struct tm *local_time;
  static char str[20]; // "YYYY-MM-DD HH:MM:SS" + '\0'
  local_time = localtime(&timestamp);
  // Format it as: "YYYY-MM-DD HH:MM:SS"
  strftime(str, sizeof(str), "%Y-%m-%d %H:%M:%S", local_time);
  return str;
}
