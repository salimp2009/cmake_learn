#pragma once

#include <iosfwd>
#include <iostream>
#include <messageExport.h>
#include <string>

#include "named_collection.hpp"
/*! \file Message.hpp */
/*! \class Message
 * \print messages with a UUID to screen
 * \author Salim Pamukcu
 * \date 2023
 */
class message_EXPORT Message {
public:
  /*! \brief Constructor from a string
   * \param[in] m a string
   */
  explicit Message(std::string m) : message_(std::move(m)) {}

  /*! \brief Constructor from a character array
   * \param[in] m a C style string; char array
   */
  explicit Message(const char *m) : message_(m) {}

  const std::string &print() const & { return this->message_; }

private:
  /*! The message to be forwarded to screen */
  std::string message_;
};

/*! UUID created for each user */
std::string getUUID();

message_EXPORT std::ostream &operator<<(std::ostream &os, const Message &obj);

template <typename T, typename... Ts>
constexpr inline bool message_NO_EXPORT are_same2 =
    std::conjunction_v<std::is_same<T, Ts>...>;

struct Test2 {
  int value2{};
  int get_value2() const;
};
