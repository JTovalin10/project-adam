#ifndef UTILS_MOVE_H_
#define UTILS_MOVE_H_

#include <type_traits>

namespace slime {
template <typename T>
constexpr decltype(auto) move(T&& t) noexcept {
  return static_cast<std::remove_reference_t<T>&&>(t);
}
}  // namespace slime

#endif  // UTILS_MOVE_H_
