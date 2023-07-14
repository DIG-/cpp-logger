#pragma once

#include <dig-logger/interface.hpp>
#include <ostream>

namespace DIG {
namespace Logger {
namespace Printer {

class Stream : public LoggerInterface {
 public:
  Stream(std::ostream& output) : output(output) {}

  virtual void log(                                    //
      const Level level,                               //
      const std::string_view tag,                      //
      const std::optional<std::exception>& exception,  //
      const std::string_view message,                  //
      const std::source_location& source               //
      ) = 0;

  void log(                                                   //
      const Level level,                                      //
      const std::string_view tag,                             //
      const std::optional<std::exception>& exception,         //
      const std::function<const std::string_view()> message,  //
      const std::source_location& source                      //
  ) {
    log(level, tag, exception, message(), source);
  }

 protected:
  std::ostream& output;
};

}  // namespace Printer
}  // namespace Logger
}  // namespace DIG