#pragma once
#include "corobase.hpp"
#include "messageExport.h"

#include <coroutine>
#include <cstddef>
#include <optional>
#include <utility>

namespace sp {

class DataStreamReader {
public:
  DataStreamReader() = default;

  // Deleting move assigment deletes copy & move operations
  // Peter Sommerlad’s approach called Destructor defined
  // Deleted Move Assignment (DesDeMovA)
  DataStreamReader &operator=(DataStreamReader &&) noexcept = delete;

  struct Awaiter {
    Awaiter &operator=(Awaiter &&) noexcept = delete;

    Awaiter(DataStreamReader &event) noexcept : mevent{event} {
      mevent.mawaiter = this;
    }

    bool await_ready() const noexcept { return mevent.mdata.has_value(); }

    void await_suspend(std::coroutine_handle<> coro_hndl) noexcept {
      // get a hold of handle of awaiting coroutine
      m_corohndl = coro_hndl;
    }

    std::byte await_resume() noexcept {
      assert(mevent.mdata.has_value());
      return *std::exchange(mevent.mdata, std::nullopt);
      // return mevent.mdata
      //     .and_then([this](std::byte val) -> std::optional<std::byte> {
      //       return *std::exchange(mevent.mdata, std::nullopt);
      //     })
      //     .value_or(std::byte{});
    }

    void resume() { m_corohndl.resume(); }

  private:
    DataStreamReader &mevent;
    std::coroutine_handle<> m_corohndl{};
  };

  // making DataStreamReader an awaitable
  auto operator co_await() noexcept { return Awaiter{*this}; }

  void set(std::byte b) {
    mdata.emplace(b);
    if (mawaiter) {
      mawaiter->resume();
    }
  }

private:
  friend struct Awaiter;
  Awaiter *mawaiter;
  std::optional<std::byte> mdata{};
};

using FSM_v2 = generator<std::string, false>;

message_EXPORT void stream_simulator2();
message_EXPORT FSM_v2 parser_v2(DataStreamReader &stream);

} // namespace sp
