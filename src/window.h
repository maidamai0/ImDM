#pragma once

#include "singleton.h"

class Window {
  enable_singleton(Window);
  Window() = default;

 public:
  void Show();
};