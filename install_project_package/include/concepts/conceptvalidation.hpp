#pragma once
#include "messageExport.h"
#include <cstdio>
namespace sp {

template <typename T>
concept has_validation = requires(T t) { t.validate(); };

template <typename T> void send_data(const T &data) {

  if constexpr (has_validation<T>) {
    data.validate();
  } else
    std::puts("No validation support");
}

class message_EXPORT ComplexType {
public:
  void validate() const; // { std::puts("Complex Type is validating data"); }
};

class message_EXPORT SimpleType {};

} // namespace sp
