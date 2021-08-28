#include "window.h"

#include "imgui/imgui.h"
#include "imgui_internal.h"

#include "assets/fork_awesome.h"
#include "font.h"
#include "i18n.h"
#include "log.h"
#include "singleton.h"
#include "util.h"

namespace {
constexpr auto navigation_margin = 30;

const auto navigation_new = i18n::translation("New");
const auto navigation_downloading = i18n::translation("Downloading");
const auto navigation_local = i18n::translation("Local");

const auto button_ok = i18n::translation("OK");
const auto button_cancel = i18n::translation("Cancel");
constexpr auto button_width = 120;
constexpr auto button_height = 30;

// colors
const auto Blue1 = util::color("#2F80ED");
const auto Gray4 = util::color("#BDBDBD");
const auto Gray5 = util::color("#E0E0E0");
}  // namespace

void Window::Show() {
  navigation_bar();

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

void Window::navigation_bar() {
  ImGui::PushFont(make_singleton<Font>().Head());
  auto size = ImGui::GetWindowSize();
  auto pos = ImGui::GetWindowPos();

  const auto navigation_new_width = ImGui::CalcTextSize(navigation_new.c_str()).x;
  const auto navigation_downloading_width = ImGui::CalcTextSize(navigation_downloading.c_str()).x;
  const auto navigation_local_width = ImGui::CalcTextSize(navigation_local.c_str()).x;
  const auto navigation_width = navigation_new_width + navigation_downloading_width + navigation_local_width +
                                ImGui::GetStyle().ItemSpacing.x * 2 + navigation_margin;
  ImGui::SetCursorPos({pos.x + size.x - navigation_width, pos.y + navigation_margin});

  auto cursor_x = ImGui::GetCursorPosX();
  if (ImGui::InvisibleButton(navigation_new.c_str(),
                             ImVec2(navigation_new_width, ImGui::GetTextLineHeightWithSpacing()))) {
    navigation_bar_ = NavigationBar::New;
  }
  ImGui::SameLine();
  ImGui::SetCursorPosX(cursor_x);
  if (navigation_bar_ == NavigationBar::New) {
    ImGui::PushStyleColor(ImGuiCol_Text, Blue1);
  } else {
    ImGui::PushStyleColor(ImGuiCol_Text, Gray4);
  }
  ImGui::TextUnformatted(navigation_new.c_str());
  ImGui::PopStyleColor();

  ImGui::SameLine();
  cursor_x = ImGui::GetCursorPosX();
  if (ImGui::InvisibleButton(navigation_downloading.c_str(),
                             ImVec2(navigation_downloading_width, ImGui::GetTextLineHeightWithSpacing()))) {
    navigation_bar_ = NavigationBar::Downloading;
  }
  ImGui::SameLine();
  ImGui::SetCursorPosX(cursor_x);
  if (navigation_bar_ == NavigationBar::Downloading) {
    ImGui::PushStyleColor(ImGuiCol_Text, Blue1);
  } else {
    ImGui::PushStyleColor(ImGuiCol_Text, Gray4);
  }
  ImGui::TextUnformatted(navigation_downloading.c_str());
  ImGui::PopStyleColor();

  ImGui::SameLine();
  cursor_x = ImGui::GetCursorPosX();
  if (ImGui::InvisibleButton(navigation_local.c_str(),
                             ImVec2(navigation_local_width, ImGui::GetTextLineHeightWithSpacing()))) {
    navigation_bar_ = NavigationBar::Local;
  }
  ImGui::SameLine();
  ImGui::SetCursorPosX(cursor_x);
  if (navigation_bar_ == NavigationBar::Local) {
    ImGui::PushStyleColor(ImGuiCol_Text, Blue1);
  } else {
    ImGui::PushStyleColor(ImGuiCol_Text, Gray4);
  }
  ImGui::TextUnformatted(navigation_local.c_str());
  ImGui::PopStyleColor();

  ImGui::PopFont();
}

void Window::new_page() {
  const auto size = ImGui::GetWindowSize();
  static const auto width = 400;
  static const auto height = 500;
  url_.resize(2048);

  ImGui::SetNextWindowPos({(size.x - width) / 2, (size.y - height) / 2});
  ImGui::BeginChild(navigation_new.c_str(), ImVec2(width, height), true, ImGuiWindowFlags_NoMove);
  ImGui::SetNextItemWidth(width - navigation_margin * 2);
  ImGui::SetCursorPos({ImGui::GetCursorPosX() + navigation_margin, ImGui::GetCursorPosY() + navigation_margin});
  ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0F);
  ImGui::InputTextWithHint("##URL", "URL", url_.data(), url_.size());
  ImGui::PopStyleVar();

  ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 2.0F);
  const auto window_size = ImGui::GetWindowSize();
  ImGui::SetCursorPos({(window_size.x - button_width * 2 - ImGui::GetStyle().ItemSpacing.x) / 2.0F,
                       window_size.y - button_height - navigation_margin});

  auto cursor_pos = ImGui::GetCursorPos();
  if (ImGui::ColorButton("cancel button", ImVec4(1.0f, 1.0f, 1.0f, 0),
                         ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoDragDrop,
                         ImVec2(button_width, button_height))) {
    LOGI("cancel button clicked");
  }
  ImGui::SameLine();
  auto cursor_pos_button = ImGui::GetCursorPos();

  auto text_size = ImGui::CalcTextSize(button_cancel.c_str());
  ImGui::SetCursorPos({cursor_pos.x + (button_width - text_size.x) / 2.0F,
                       cursor_pos.y + (button_height - text_size.y - ImGui::GetStyle().FramePadding.y * 2) / 2.0F});
  ImGui::TextUnformatted(button_cancel.c_str());

  ImGui::SameLine();
  ImGui::SetCursorPos(cursor_pos_button);
  cursor_pos = ImGui::GetCursorPos();
  if (ImGui::ColorButton("ok button", Blue1, ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoDragDrop,
                         ImVec2(button_width, button_height))) {
    LOGI("ok button clicked");
  }
  ImGui::SameLine();

  text_size = ImGui::CalcTextSize(button_ok.c_str());
  ImGui::SetCursorPos({cursor_pos.x + (button_width - text_size.x) / 2.0F,
                       cursor_pos.y + (button_height - text_size.y - ImGui::GetStyle().FramePadding.y * 2) / 2.0F});
  ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
  ImGui::TextUnformatted(button_ok.c_str());
  ImGui::PopStyleColor();

  ImGui::PopStyleVar();
  ImGui::EndChild();
}

void Window::downloading_page() {
  const auto size = ImGui::GetWindowSize();

  ImGui::SetNextWindowPos({navigation_margin, navigation_margin * 2});
  ImGui::BeginChild(navigation_new.c_str(), ImVec2(size.x - navigation_margin * 2, size.y - navigation_margin * 3),
                    false, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar);

  ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
  for (int i = 0; i < 200; ++i) {
    ImGuiID child_id = ImGui::GetID((void*)(intptr_t)i);
    ImGui::BeginChild(child_id, {0, 60}, true, ImGuiWindowFlags_NoMove);
    ImGui::PushFont(make_singleton<Font>().AwesomeFont());
    ImGui::TextUnformatted(ICON_FK_PAUSE_CIRCLE_O);
    ImGui::PopFont();
    ImGui::TextUnformatted("file.txt");
    ImGui::EndChild();
  }
  ImGui::PopStyleColor();

  ImGui::EndChild();
}

void Window::local_page() {
  const auto size = ImGui::GetWindowSize();

  ImGui::SetNextWindowPos({navigation_margin, navigation_margin * 2});
  ImGui::BeginChild(navigation_new.c_str(), ImVec2(size.x - navigation_margin * 2, size.y - navigation_margin * 3),
                    true, ImGuiWindowFlags_NoMove);
  ImGui::TextUnformatted(navigation_local.c_str());
  ImGui::EndChild();
}
