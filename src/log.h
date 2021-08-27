#pragma once

#define LOGD SPDLOG_DEBUG
#define LOGI SPDLOG_INFO
#define LOGW SPDLOG_WARN
#define LOGE SPDLOG_ERROR

#ifndef NDEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#endif

#include "singleton.h"
#include "spdlog/spdlog.h"
#include "spdlog/stopwatch.h"

class Log {
  enable_singleton(Log);
  Log();

 public:
  ~Log();
};