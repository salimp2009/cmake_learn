#pragma once
#include "messageExport.h"
#include <cstddef>
#include <string>

struct message_EXPORT named_object {
  std::string name{};
};

struct message_EXPORT named_collection {
  std::string name{};
  std::size_t size{};
  explicit named_collection() = default;
  operator named_object() const { return {name}; }
};
