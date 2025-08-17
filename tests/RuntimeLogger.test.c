#include <criterion/criterion.h>
#include <logger/logger.h>
#include <stdio.h>
#define T LOG

static void setup(void) {
  LOG_runtimeLogger_reset();
  runtimeLogger_mode = LOG_RuntimeLogger_mode_silent;
}

static void teardown(void){
  return;
}

Test(T, LOG_Log_fields, .fini = teardown, .init = setup) {
  time_t t;
  time(&t);
  int line = __LINE__ + 1;
  LOG_ERROR("error");
  LOG_Log log = LOG_runtimeLogger_get_last_log();
  cr_expect_eq(strcmp(log.message, "error"), 0, "wrong message");
  printf("file: %s\n", log.file);
  cr_expect_eq(strcmp(log.file, "tests/RuntimeLogger.test.c"), 0, "wrong file name" );
  cr_expect_eq(log.line, line, "wrong line");
  time_t time = log.timestamp;
  cr_expect_eq(time, t, "wrong timestamp");
}

Test(T, LOG_ERROR, .fini = teardown, .init = setup) {
  LOG_ERROR("error");
  LOG_Log log = LOG_runtimeLogger_get_last_log();
  cr_expect_eq(log.code, LOG_RuntimeLogger_code_error, "wrong code");
}

Test(T, LOG_WARNING, .fini = teardown, .init = setup) {
  LOG_WARNING("warning");
  LOG_Log log = LOG_runtimeLogger_get_last_log();
  cr_expect_eq(log.code, LOG_RuntimeLogger_code_warning, "wrong code");
}

Test(T, LOG_INFO, .fini = teardown, .init = setup) {
  LOG_INFO("info");
  LOG_Log log = LOG_runtimeLogger_get_last_log();
  cr_expect_eq(log.code, LOG_RuntimeLogger_code_info, "wrong code");
}

Test(T, LOG_SUCCESS, .fini = teardown, .init = setup) {
  LOG_SUCCESS("success");
  LOG_Log log = LOG_runtimeLogger_get_last_log();
  cr_expect_eq(log.code, LOG_RuntimeLogger_code_success, "wrong code");
}
#undef T
