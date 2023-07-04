#include "dig-logger/printer/stdout.hpp"

#include <dig-logger/printer/formatter.hpp>
#include <iomanip>

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
  set_color(Level::NONE);
}

}  // namespace Printer
}  // namespace Logger
}  // namespace DIG