#pragma once

#include <dig-logger/interface.hpp>

namespace DIG {
namespace Logger {
namespace Printer {

class Stub : public LoggerInterface {
 public:
  Stub(){};

  void log(                                            //
      const Level level,                               //
      const std::string_view tag,                      //
      const std::optional<std::exception>& exception,  //
      const std::string_view message,                  //
      const std::source_location& source               //
  ){};

  void log(                                                   //
      const Level level,                                      //
      const std::string_view tag,                             //
      const std::optional<std::exception>& exception,         //
      const std::function<const std::string_view()> message,  //
      const std::source_location& source                      //
  ) {}
};

}  // namespace Printer
}  // namespace Logger
}  // namespace DIG