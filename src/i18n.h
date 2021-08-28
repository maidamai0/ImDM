#pragma once

#include <string>

namespace i18n {
std::string translation(std::string_view id) noexcept {
  return std::string(id);
}

#define tr(x) i18n::translation(x)

}  // namespace i18n