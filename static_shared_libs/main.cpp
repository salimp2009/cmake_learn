#include "message.hpp"
#include <Eigen/Dense>
#include <cstdlib>
#include <iostream>
#include <memory>
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

int main(int argc, char *argv[]) {
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

  return 0;
}
