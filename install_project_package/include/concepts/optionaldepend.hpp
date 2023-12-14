#pragma once
#include "messageExport.h"

#include <concepts>
#include <initializer_list>
#include <optional>
#include <type_traits>
#include <utility>
namespace sp {

namespace message_NO_EXPORT detail {

// forward declaration to use in concept below
template <typename T>
  requires(not std::is_same_v<T, std::in_place_t>) &&
          (not std::is_same_v<T, std::nullopt_t>)
class opt;

// concepts for opt
template <class T, class U, class Other>
concept enable_from_other = std::is_constructible_v<T, Other> &&
                            !std::is_constructible_v<T, opt<U> &> &&
                            !std::is_constructible_v<T, opt<U> &&> &&
                            !std::is_constructible_v<T, const opt<U> &> &&
                            !std::is_constructible_v<T, const opt<U> &&> &&
                            !std::is_convertible_v<opt<U> &, T> &&
                            !std::is_convertible_v<opt<U> &&, T> &&
                            !std::is_convertible_v<const opt<U> &, T> &&
                            !std::is_convertible_v<const opt<U> &&, T>;
template <class T, class U>
concept enable_assign_forward =
    !std::is_same_v<opt<T>, std::decay_t<U>> && !std::is_scalar_v<T> &&
    !std::is_constructible_v<T, U> && !std::is_assignable_v<T &, U>;

template <typename T> struct opt_storage_base {
  constexpr opt_storage_base() noexcept : m_empty{}, m_has_value{false} {}

  template <typename... U>
  constexpr opt_storage_base(std::in_place_t, U &&...args) noexcept
      : m_value{std::forward<U>(args)...}, m_has_value{true} {}

  ~opt_storage_base()
    requires(not std::is_trivially_destructible_v<T>)
  {
    if (m_has_value) {
      m_value.~T();
      m_has_value = false;
    }
  }
  ~opt_storage_base() = default;

  struct empty {};
  union {
    empty m_empty{};
    T m_value;
  };
  bool m_has_value{};
};

template <typename T> struct opt_operations_base : opt_storage_base<T> {
  using opt_storage_base<T>::opt_storage_base;

  opt_operations_base() = default;

  opt_operations_base(const opt_operations_base &rhs)
    requires(not std::is_trivially_copy_constructible_v<T>)
      : opt_storage_base<T>() {
    if (rhs.has_value()) {
      this->construct(rhs.get());
    } else {
      this->m_has_value = false;
    }
  }

  opt_operations_base(opt_operations_base &&rhs) noexcept(
      std::is_nothrow_move_constructible_v<T>)
    requires(not std::is_trivially_move_constructible_v<T>)
  {
    if (rhs.has_value()) {
      this->construct(std::move(rhs.get()));
    } else {
      this->m_has_value = false;
    }
  }

  opt_operations_base &operator=(const opt_operations_base &rhs)
    requires(not std::is_trivially_copy_assignable_v<T>)
  {
    this->assign(rhs);
    return *this;
  }

  opt_operations_base &operator=(const opt_operations_base &&rhs) noexcept(
      std::is_nothrow_move_constructible_v<T> &&
      std::is_nothrow_move_assignable_v<T>)
    requires(not std::is_trivially_move_assignable_v<T>)
  {
    this->assign(std::move(rhs));
    return *this;
  }
  opt_operations_base(const opt_operations_base &rhs)
    requires(std::is_copy_constructible_v<T>)
  = default;

  opt_operations_base(opt_operations_base &&rhs) noexcept
    requires(std::is_move_constructible_v<T>)
  = default;

  opt_operations_base &operator=(const opt_operations_base &)
    requires(std::is_copy_assignable_v<T>)
  = default;

  opt_operations_base &operator=(opt_operations_base &&) noexcept(
      std::is_move_constructible_v<T> && std::is_nothrow_move_assignable_v<T>)
    requires(std::is_move_assignable_v<T>)
  = default;

  ~opt_operations_base() = default;

  void hard_reset() noexcept {
    this->get().~T();
    this->m_has_value = false;
  }

  template <class Opt> void assign(Opt &rhs) {
    if (this->has_value()) {
      if (rhs.has_value()) {
        this->m_value = std::forward<Opt>(rhs.get());
      } else {
        this->m_value.~T();
        this->m_has_value = false;
      }

    } else if (rhs.has_value()) {
      construct(std::forward<Opt>(rhs.get()));
    }
  }

  template <typename... Args>
  void construct(Args... args) noexcept(
      std::is_nothrow_constructible_v<T, Args...>) {
    // if C++20
    std::construct_at(std::addressof(this->m_value),
                      std::forward<Args>(args)...);
    // if not C++20
    // ::new (std::addressof(this->value)) T(std::forward<Args>(args)...);

    this->m_has_value = true;
  }

  bool has_value() const { return this->m_has_value; }

  constexpr T &get() & { return this->m_value; }
  constexpr const T &get() const & { return this->m_value; }
  constexpr T &&get() && noexcept { return std::move(this->m_value); }
};

template <class T>
  requires(not std::is_same_v<T, std::in_place_t>) &&
          (not std::is_same_v<T, std::nullopt_t>)
class opt : public opt_operations_base<T> {

  using base = opt_operations_base<T>;

public:
  // TODO: implement reset() function
  opt take() {
    opt ret = std::move(*this);
    // reset();
    return ret;
  }

  constexpr opt() = default;
  constexpr explicit opt(std::nullopt_t) noexcept {}
  constexpr opt(const opt &rhs) = default;
  constexpr opt(opt &&rhs) noexcept = default;

  constexpr opt &operator=(const opt &rhs) = default;
  constexpr opt &operator=(opt &&rhs) noexcept = default;

  template <class... Args>
    requires(std::is_constructible_v<T, Args...>)
  constexpr explicit opt(std::in_place_t, Args... args)
      : base(std::in_place, std::forward<Args>(args)...) {}

  template <typename U, class... Args>
    requires(
        std::is_constructible_v<T, std::initializer_list<U> &, Args && ...>)
  constexpr explicit opt(std::in_place_t, std::initializer_list<U> il,
                         Args &&...args) {
    this->construct(il, std::forward<Args>(args)...);
  }

  template <class U = T>
    requires(std::is_convertible_v<U &&, T>)
  constexpr explicit opt(U &&u) : base(std::in_place, std::forward<U>(u)) {}

  template <class U = T>
    requires(not std::is_convertible_v<U &&, T>)
  constexpr explicit opt(U &&u) : base(std::in_place, std::forward<U>(u)) {}

  // converting copy-constructor
  template <class U>
    requires(enable_from_other<T, U, const U &> &&
             std::is_convertible_v<const U &, T>)

  constexpr opt(const opt<U> &rhs) {
    if (rhs.has_value()) {
      this->construct(*rhs);
    }
  }

  template <class U>
    requires(enable_from_other<T, U, const U &> &&
             not std::is_convertible_v<const U &, T>)

  constexpr opt(const opt<U> &rhs) {
    if (rhs.has_value()) {
      this->construct(*rhs);
    }
  }

  // converting move constructor
  template <class U>
    requires(enable_from_other<T, U, U &&> &&
             std::is_convertible_v<const U &, T>)
  constexpr opt(const opt<U> &rhs) {
    if (rhs.has_value()) {
      this->construct(std::move(*rhs));
    }
  }

  template <class U>
    requires(enable_from_other<T, U, U &&> &&
             not std::is_convertible_v<const U &, T>)
  constexpr opt(const opt<U> &rhs) {
    if (rhs.has_value()) {
      this->construct(std::move(*rhs));
    }
  }

  ~opt() = default;

  // Destroy current value if there is any
  opt &operator=(std::nullopt_t) noexcept {
    if (this->has_value()) {
      this->m_value.~T();
      this->m_has_value = false;
    }
    return *this;
  }
  // template<class U>
  // requires std::is_assignable_v<T&, U>
};

// std::optional<std::vector<int>> myopt2{std::in_place, {1, 2, 3, 4}};
// std::optional<int> myopt{1};
// opt<int> myopt2{1};
} // namespace message_NO_EXPORT detail

} // namespace sp
