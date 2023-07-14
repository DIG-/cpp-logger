#pragma once

#include <dig-logger/level.hpp>
#include <ostream>

namespace DIG {
namespace Logger {
namespace Printer {
namespace Formatter {

void current_date(std::ostream& output);
const char level_short(const Level level);
const char* level_long(const Level level);

}  // namespace Formatter
}  // namespace Printer
}  // namespace Logger
}  // namespace DIG