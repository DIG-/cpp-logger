#include "dig-logger/util/filter.hpp"

namespace DIG {
namespace Logger {
namespace Util {

void Filter::log(                                    //
    const Level level,                               //
    const std::string_view tag,                      //
    const std::optional<std::exception>& exception,  //
    const std::string_view message,                  //
    const std::source_location& source               //
) {
  if (level < minimum || level > maximum) return;
  parent->log(level, tag, exception, message, source);
}

void Filter::log(                                           //
    const Level level,                                      //
    const std::string_view tag,                             //
    const std::optional<std::exception>& exception,         //
    const std::function<const std::string_view()> message,  //
    const std::source_location& source                      //
) {
  if (level < minimum || level > maximum) return;
  parent->log(level, tag, exception, message, source);
}

}  // namespace Util
}  // namespace Logger
}  // namespace DIG