/**
 * Copyright (c) 2020 rxi
 * https://github.com/rxi/log.c
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See `log.c` for details.
 */

#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>

__BEGIN_DECLS

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define LOG_VERSION "0.1.0"

typedef struct {
  va_list ap;
  const char *fmt;
  const char *file;
  const char *func;
  struct tm *time;
  long time_ms;
  void *udata;
  int line;
  int level;
} log_Event;

typedef void (*log_LogFn)(log_Event *ev);
typedef void (*log_LockFn)(bool lock, void *udata);

enum { QLOG_TRACE, QLOG_DEBUG, QLOG_INFO, QLOG_WARN, QLOG_ERROR, QLOG_FATAL };

#define log_trace(...) log_log(QLOG_TRACE, __FILENAME__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define log_debug(...) log_log(QLOG_DEBUG, __FILENAME__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define log_info(...)  log_log(QLOG_INFO,  __FILENAME__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define log_warn(...)  log_log(QLOG_WARN,  __FILENAME__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define log_error(...) log_log(QLOG_ERROR, __FILENAME__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define log_fatal(...) log_log(QLOG_FATAL, __FILENAME__, __FUNCTION__, __LINE__, __VA_ARGS__)

const char* log_level_string(int level);
void log_set_lock(log_LockFn fn, void *udata);
void log_set_level(int level);
void log_set_quiet(bool enable);
int log_add_callback(log_LogFn fn, void *udata, int level);
int log_add_fp(FILE *fp, int level);

void log_log(int level, const char *file, const char *func, int line, const char *fmt, ...);

__END_DECLS

#endif
