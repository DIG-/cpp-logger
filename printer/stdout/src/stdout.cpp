#include "dig-logger/printer/stdout.hpp"

#include <chrono>
#include <iomanip>
#include <sstream>

namespace DIG {
namespace Logger {
namespace Printer {

void StdOut::log(                                    //
    const Level level,                               //
    const std::string_view tag,                      //
    const std::optional<std::exception>& exception,  //
    const std::string_view message,                  //
    const std::source_location& source               //
) {
  std::lock_guard lock(mutex);
  set_color(level);

  auto now = std::chrono::system_clock::now();
  auto clock = std::chrono::system_clock::to_time_t(now);
  auto time = std::gmtime(&clock);
  uint_fast16_t offset = (time->tm_hour * 60) + time->tm_min;
  time = std::localtime(&clock);
  offset -= (time->tm_hour * 60) + time->tm_min;
  char signal = "+-"[offset > 0];
  offset = std::abs(offset);
  output << std::put_time(time, "%Y-%m-%dT%H:%M:%S") << "." << std::setw(3) << std::setfill('0')
         << std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() % 1000;
  output << signal << std::setw(4) << std::setfill('0') << (((offset / 60) * 100) + (offset % 60));

  output << " [" << level_representation(level) << "]";
  output << " " << source.file_name() << "@" << std::setw(4) << std::setfill('0') << source.line();
  output << " " << tag << ": " << message;

  if (exception.has_value()) {
    if (!message.empty()) {
      output << " :: ";
    }
    output << exception->what();
  }
  output << "\n";
  set_color(Level::NONE);
}

const char StdOut::level_representation(const Level level) {
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

}  // namespace Printer
}  // namespace Logger
}  // namespace DIG