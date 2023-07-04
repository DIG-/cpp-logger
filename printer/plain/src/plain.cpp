#include "dig-logger/printer/plain.hpp"

#include <dig-logger/printer/formatter.hpp>
#include <iomanip>

namespace DIG {
namespace Logger {
namespace Printer {

void Plain::log(                                     //
    const Level level,                               //
    const std::string_view tag,                      //
    const std::optional<std::exception>& exception,  //
    const std::string_view message,                  //
    const std::source_location& source               //
) {
  std::lock_guard lock(mutex);

  Formatter::current_date(output);
  output << " [" << Formatter::level_short(level) << "]";
  output << " " << source.file_name() << "@" << std::setw(4) << std::setfill('0') << source.line();
  output << " " << tag << ": " << message;

  if (exception.has_value()) {
    if (!message.empty()) {
      output << " :: ";
    }
    output << exception->what();
  }
  output << "\n";
}

void Plain::header() {
  log(Level::VERBOSE, "Logger", std::optional<std::exception>(), "Init", std::source_location::current());
}

void Plain::footer() {
  log(Level::VERBOSE, "Logger", std::optional<std::exception>(), "Finish", std::source_location::current());
}

}  // namespace Printer
}  // namespace Logger
}  // namespace DIG