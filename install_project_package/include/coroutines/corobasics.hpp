#pragma once

#include "messageExport.h"
#include <coroutine>
#include <type_traits>
namespace sp {

message_EXPORT void coroutines_basics1() noexcept;

// std::generator<char> letters(char first) {
//   for (;; co_yield first++)
//     ;
// }
} // namespace sp
