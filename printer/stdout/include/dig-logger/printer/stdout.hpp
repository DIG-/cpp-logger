#pragma once

#include <dig-logger/interface.hpp>
#include <dig-logger/printer/stream.hpp>
#include <iostream>
#include <mutex>

namespace DIG {
namespace Logger {
namespace Printer {

class StdOut : public Stream {
 public:
  StdOut() : Stream(std::cout) {}
  ~StdOut() {}
  void log(                                            //
      const Level level,                               //
      const std::string_view tag,                      //
      const std::optional<std::exception>& exception,  //
      const std::string_view message,                  //
      const std::source_location& source               //
  );

 private:
  std::mutex mutex;
  void set_color(const Level level);
  const char level_representation(const Level level);
};

}  // namespace Printer
}  // namespace Logger
}  // namespace DIG