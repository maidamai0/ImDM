#pragma once

#include "singleton.h"

#include <string>

class Window {
  enable_singleton(Window);
  Window() = default;

 public:
  void Show();
  void Page() {
    switch (navigation_bar_) {
      case NavigationBar::New:
        new_page();
        break;
      case NavigationBar::Downloading:
        downloading_page();
        break;
      case NavigationBar::Local:
        local_page();
        break;
    }
  }

 private:
  void navigation_bar();
  void new_page();
  void downloading_page();
  void local_page();

  enum class NavigationBar {
    New,
    Downloading,
    Local,
  };

  NavigationBar navigation_bar_ = NavigationBar::New;
  std::string url_;
};