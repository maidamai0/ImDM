#pragma once

/**
 * @brief make a sigleton
 * @details make consturctor of T private and let this function be friends of T
 * @tparam T    singleton type
 * @return      T
 */
template <typename T>
auto make_singleton() -> T& {
  static T instance;
  return instance;
}

#define no_copy(T)      \
  T(const T&) = delete; \
  auto operator=(const T&)->T& = delete

#define no_move(T) \
  T(T&&) = delete; \
  auto operator=(T&&)->T& = delete

#define enable_singleton(T)            \
  friend auto make_singleton<T>()->T&; \
                                       \
 public:                               \
  no_copy(T);                          \
  no_move(T);                          \
                                       \
 private:
