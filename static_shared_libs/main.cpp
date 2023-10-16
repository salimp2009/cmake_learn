
#include <Eigen/Dense>
#include <boost/filesystem.hpp>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <memory>
#include <numeric>
#include <ranges>

#include "message.hpp"
#include "sum_integers.hpp"
#include <vector>

#define PY_SSIZE_T_CLEAN
#include <python3.11/Python.h>
#include <python3.11/pylifecycle.h>
std::string operating_system_info() {

#ifdef Is_Windows
  return std::string("Hello from Windows!");
#elif Is_Linux
  return std::string("Hello from Linux!");
#elif Is_Darwin
  return std::string("Hello from macOS!");
#else
  return std::string("Hello from an unknown system!");
#endif
}

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

std::string arch_info() {
  std::string arch_info(TOSTRING(ARCHITECTURE));
  arch_info += std::string(" architecture. ");
#ifdef IS_32_BIT_ARCH
  return arch_info + std::string("Compiled on a 32 bit host processor.");
#elif IS_64_BIT_ARCH
  return arch_info + std::string("Compiled on a 64 bit host processor.");
#else
  return arch_info + std::string("Neither 32 nor 64 bit, puzzling ...");
#endif
}
int sum_integers2(const std::vector<int> &integers) {
  auto sum = 0;

  auto result = std::accumulate(std::begin(integers), std::end(integers), sum);
  return result;
}

int main(int argc, const char *argv[]) {
  Message msg("Hello cmake");
  const auto sptr = std::make_shared<int>(5);
  auto sptr2 = sptr;
  std::cout << msg << "\n ptr: " << *sptr << ", ptr2: " << *sptr2 << '\n';
  std::cout << operating_system_info() << '\n';
  std::cout << arch_info() << '\n';
  Eigen::MatrixXd A = Eigen::MatrixXd::Random(7, 10);

  // Py_SetProgramName(argv[0]); /* optional but recommended */
  Py_Initialize();
  PyRun_SimpleString("from time import time, ctime\n"
                     "print('Today is',ctime(time()))\n");
  Py_Finalize();

  std::vector<int> integers;
  // auto count = std::size(&argv[0]);
  for (const auto i : std::ranges::views::iota(0, argc))
  /*     for (auto i = 1; i < argc; i++) */ {
    integers.push_back(i);
  }
  auto sum = sum_integers2(integers);
  // auto sum2 = sum_integers3(integers);
  std::cout << sum << "" << '\n';
  return 0;
}
