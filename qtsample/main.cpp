// #include <QtGui/QAccessible>
#include <cstdio>
#include <qapplicationstatic.h>
#include <qdatetime.h>

auto main(int argc, char *argv[]) -> int {
  QCoreApplication app(argc, argv);
  // using namespace std::string_view_literals;
  QDate date{2024, 3, 20};
  std::printf("Hello Qt day: %d month: %d", date.day(), date.month());
}
