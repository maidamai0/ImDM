#pragma once

#include "imgui/imgui.h"
#include "string_view"

#include "assets/droid_sans.h"

#include <cstdio>

namespace util {
ImVec4 color(std::string_view name) {
  int r = 0;
  int g = 0;
  int b = 0;
  std::sscanf(name.data(), "#%02x%02x%02x", &r, &g, &b);
  return ImVec4(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
}
}  // namespace util