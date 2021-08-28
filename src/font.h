#pragma once

#include "imgui/imgui.h"

#include "singleton.h"
#include "string"

class Font {
  enable_singleton(Font);

 public:
  ImFont* Head();
  ImFont* Body();
  ImFont* AwesomeFont();

 private:
  Font();

  ImFont* head_font_ = nullptr;
  ImFont* body_font_ = nullptr;
  ImFont* awesome_font_ = nullptr;
};