#include <QCommandLineParser>
#include <cstdio>
#include <qapplicationstatic.h>
#include <qcoreapplication.h>
#include <qcoreevent.h>
#include <qdatetime.h>
#include <qwindowdefs.h>

auto main(int argc, char *argv[]) -> int {
  QCoreApplication app(argc, argv);
  QCommandLineParser parser;
  // using namespace std::string_view_literals;
  QDate date{2024, 3, 20};
}
