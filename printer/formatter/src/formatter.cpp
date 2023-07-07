#include "dig-logger/printer/formatter.hpp"

#include <chrono>
#include <iomanip>

namespace DIG {
namespace Logger {
namespace Printer {
namespace Formatter {

void current_date(std::ostream& output) {
  auto now = std::chrono::system_clock::now();
  auto clock = std::chrono::system_clock::to_time_t(now);
  auto time = std::gmtime(&clock);
  time_t offset = (time->tm_hour * 60) + time->tm_min;
  time = std::localtime(&clock);
  offset -= (time->tm_hour * 60) + time->tm_min;
  char signal = "+-"[offset > 0];
  offset = std::abs(offset);
  output << std::put_time(time, "%Y-%m-%dT%H:%M:%S") << "." << std::setw(3) << std::setfill('0')
         << std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() % 1000;
  output << signal << std::setw(4) << std::setfill('0') << (((offset / 60) * 100) + (offset % 60));
}

const char level_short(const Level level) {
  switch (level) {
    case Level::NONE:
      return ' ';
    case Level::VERBOSE:
      return 'V';
    case Level::DEBUG:
      return 'D';
    case Level::INFORMATION:
      return 'I';
    case Level::WARNING:
      return 'W';
    case Level::ERROR:
      return 'E';
    case Level::ASSERT:
      return '!';
    default:
      return '?';
  }
}

const char* level_long(const Level level) {
  switch (level) {
    case Level::NONE:
      return "none";
    case Level::VERBOSE:
      return "verbose";
    case Level::DEBUG:
      return "debug";
    case Level::INFORMATION:
      return "info";
    case Level::WARNING:
      return "warning";
    case Level::ERROR:
      return "error";
    case Level::ASSERT:
      return "assert";
    default:
      return "unknown";
  }
}

}  // namespace Formatter
}  // namespace Printer
}  // namespace Logger
}  // namespace DIG