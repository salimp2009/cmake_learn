#include <coroutine>
#include <messageExport.h>

#include <cstddef>
#include <optional>
#include <utility>

namespace sp {

[[maybe_unused]] constinit static std::byte ESC{'H'};
[[maybe_unused]] constinit static std::byte SOF{0x10};

template <typename T> struct awaitable_promise_type_base {
  std::optional<T> m_recentSignal;

  struct awaiter {
    // a reference to outer optional
    std::optional<T> &m_recentsignal;

    bool await_ready() { return m_recentsignal.has_value(); }
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

// forward declaration
// T for store value
// G is for generator
template <typename T, typename G, typename... Bases>
struct promise_type_multibase : Bases... {

  std::optional<T> m_value{};
};

template <typename T, typename U> struct [[nodiscard]] async_generator {
  using promise_type = promise_type_multibase<T, async_generator,
                                              awaitable_promise_type_base<U>>;

  using promisetypehandle = std::coroutine_handle<promise_type>;

  T operator()() {
    auto tmp{std::move(m_corohandle.from_promise().m_value)};
    // set it to a defined state after move above
    m_corohandle.promise().m_value.clear();
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

// remove this to cpp file once it is properly implemented
struct FSM;

// this needs to in cpp file
// FSM parse() {
//   while (true) {
//     std::byte b = co_wait std::byte{};
//     if (ESC != b) {
//       continue;
//     }

//     b = co_wait std::byte{};
//     if (SOF != b) {
//       continue;
//     }
//     std::string frame{};
//     while (true) {
//       b = co_wait std::byte{};

//       if (ESC != b) {
//         b = co_await std::byte;
//         if (SOF == b) {
//           co_yield frame;
//           break;
//         } else if (ESC != b) {
//           break;
//         }
//       }

//       frame += static_cast<char>(b);
//     }
//   }
// }

} // namespace sp
