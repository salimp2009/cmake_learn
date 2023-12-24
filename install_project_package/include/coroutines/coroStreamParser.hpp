#include "corobase.hpp"
#include "coropromise_multibase.hpp"
#include "messageExport.h"

#include <cassert>
#include <coroutine>
#include <cstddef>
#include <optional>
#include <string>
#include <utility>

namespace sp {

[[maybe_unused]] static const std::byte ESC{'H'};
[[maybe_unused]] static const std::byte SOF{0x10};

inline std::byte operator""_B(char c) { return static_cast<std::byte>(c); }
inline std::byte operator""_B(unsigned long long c) {
  return static_cast<std::byte>(c);
}

template <typename T> struct awaitable_promise_type_base {
  std::optional<T> m_recentSignal;

  struct awaiter {
    // a reference to outer optional
    std::optional<T> &m_recentsignal;

    // if result is false it is suspended & await_suspend is called
    bool await_ready() { return m_recentsignal.has_value(); }
    // if await_suspend returns void, control is immediately returned to the
    // caller/resumer of the current coroutine (this coroutine remains
    // suspended), otherwise
    /* if await_suspend returns bool,
        - the value true returns control
        to the caller/resumer of the current coroutine
        - the value false resumes the current coroutine.
    */
    void await_suspend(std::coroutine_handle<>) {}
    T await_resume() {
      assert(m_recentsignal.has_value());
      auto tmp = *m_recentsignal;
      m_recentsignal.reset();
      return tmp;
    }
  };

  [[nodiscard]] awaiter await_transform(T) { return awaiter{m_recentSignal}; }
};

template <typename T>
concept has_clear = requires(T t) { t.clear(); };

// this is specialized for string;
// TODO: make a template base for a generic base
template <has_clear T, typename U> struct [[nodiscard]] async_generator {
  using promise_type = promise_type_multibase<T, async_generator,
                                              awaitable_promise_type_base<U>>;

  using promisetypehandle = std::coroutine_handle<promise_type>;

  T operator()() {
    auto tmp{std::move(m_corohandle.promise().mvalue)};
    // set it to a defined state after move above
    // clear is member function of string; this generator is custom
    m_corohandle.promise().mvalue.clear();
    return tmp;
  }

  void send_signal(U signal) {
    m_corohandle.promise().m_recentSignal = signal;
    if (not m_corohandle.done()) {
      m_corohandle.resume();
    }
  }

  // move only
  async_generator(const async_generator &) = delete;
  async_generator(async_generator &&rhs)
      : m_corohandle{std::exchange(rhs.m_corohandle, nullptr)} {}

  ~async_generator() {
    if (m_corohandle) {
      m_corohandle.destroy();
    }
  }

private:
  // default constrctr is private, we need promise to be friend
  friend promise_type;

  explicit async_generator(promise_type *p)
      : m_corohandle(promisetypehandle::from_promise(*p)) {}

  promisetypehandle m_corohandle;
};

using FSM = async_generator<std::string, std::byte>;

message_EXPORT generator<std::byte> sender(std::vector<std::byte> fakeBytes);

message_EXPORT void process_stream(generator<std::byte> &stream, FSM &parse);

void handle_frame(std::string_view sv);

message_EXPORT FSM parser();
// this needs to in cpp file

message_EXPORT void simulate_stream();

} // namespace sp
