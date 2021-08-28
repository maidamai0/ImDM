#include "font.h"
#include "assets/NotoSans-Bold.h"
#include "assets/NotoSans-Regular.h"
#include "assets/fork_awesome.h"
#include "assets/fork_awesome_webfont.h"

ImFont* Font::Head() {
  return head_font_;
}

ImFont* Font::Body() {
  return body_font_;
}

ImFont* Font::AwesomeFont() {
  return awesome_font_;
}

Font::Font() {
  ImGuiIO& io = ImGui::GetIO();
  io.Fonts->Clear();
  body_font_ = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(noto_sans_regular_compressed_data,
                                                                    noto_sans_regular_compressed_size, 18);
  head_font_ = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(noto_sans_bold_compressed_data,
                                                                    noto_sans_bold_compressed_size, 28);

  ImFontConfig config;
  config.MergeMode = true;
  config.PixelSnapH = true;
  config.GlyphMinAdvanceX = 18;
  static const ImWchar icon_ranges[] = {ICON_MIN_FK, ICON_MAX_FK, 0};
  awesome_font_ = io.Fonts->AddFontFromMemoryCompressedTTF(fork_awesome_compressed_data, fork_awesome_compressed_size,
                                                           18, &config, icon_ranges);
}
