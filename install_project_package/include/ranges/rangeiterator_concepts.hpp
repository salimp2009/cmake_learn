#pragma once
#include "messageExport.h"
#include <ranges>
namespace sp {

template <typename T>
concept continuesRange = std::ranges::contiguous_range<T>;

template <typename T>
concept randomaccessRange = std::ranges::random_access_range<T>;

template <typename T>
concept bidirectionalRange = std::ranges::bidirectional_range<T>;

template <typename T>
concept forwardRange = std::ranges::forward_range<T>;

message_EXPORT void ranges_type_checks();

} // namespace sp
