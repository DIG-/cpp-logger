#include "dig-logger/printer/stdout.hpp"

#include <windows.h>

namespace DIG {
namespace Logger {
namespace Printer {

#undef ERROR

void StdOut::set_color(const Level level) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  switch (level) {
    case Level::NONE:
      SetConsoleTextAttribute(hConsole, 0x07);
      break;
    case Level::VERBOSE:
      SetConsoleTextAttribute(hConsole, 0x08);
      break;
    case Level::DEBUG:
      SetConsoleTextAttribute(hConsole, 0x07);
      break;
    case Level::INFORMATION:
      SetConsoleTextAttribute(hConsole, 0x0b);
      break;
    case Level::WARNING:
      SetConsoleTextAttribute(hConsole, 0x06);
      break;
    case Level::ERROR:
      SetConsoleTextAttribute(hConsole, 0x04);
      break;
    case Level::ASSERT:
      SetConsoleTextAttribute(hConsole, 0x0d);
      break;
    default:
      SetConsoleTextAttribute(hConsole, 0x07);
      break;
  }
}

}  // namespace Printer
}  // namespace Logger
}  // namespace DIG