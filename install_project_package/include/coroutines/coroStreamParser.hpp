#include <messageExport.h>

#include <cstddef>

namespace sp {

constinit static std::byte ESC{'H'};
constinit static std::byte SOF{0x10};

// remove this once it is properly implemented
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
