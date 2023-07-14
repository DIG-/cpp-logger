#include "dig-logger/printer/stdout.hpp"

namespace DIG {
namespace Logger {
namespace Printer {

void StdOut::set_color(const Level level) {
  switch (level) {
    case Level::NONE:
      output << "\x1b[0m";
      break;
    case Level::VERBOSE:
      output << "\x1b[90m";
      break;
    case Level::DEBUG:
      output << "\x1b[37m";
      break;
    case Level::INFORMATION:
      output << "\x1b[36m";
      break;
    case Level::WARNING:
      output << "\x1b[93m";
      break;
    case Level::ERROR:
      output << "\x1b[31m";
      break;
    case Level::ASSERT:
      output << "\x1b[35m";
      break;
    default:
      output << "\x1b[0m";
      break;
  }
}

}  // namespace Printer
}  // namespace Logger
}  // namespace DIG