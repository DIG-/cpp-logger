#pragma once

#include <array>
#include <dig-logger/interface.hpp>
#include <memory>

namespace DIG {
namespace Logger {
namespace Util {

template <std::size_t N>
class Union : public LoggerInterface {
  static_assert(N > 1, "Union is only available with more than one LoggerInterface");

 public:
  Union(std::array<std::unique_ptr<LoggerInterface>, N>& loggers) : loggers(std::move(loggers)){};
  Union(std::array<std::unique_ptr<LoggerInterface>, N>&& loggers) : loggers(std::move(loggers)){};
  ~Union(){};

  void log(                                            //
      const Level level,                               //
      const std::string_view tag,                      //
      const std::optional<std::exception>& exception,  //
      const std::string_view message,                  //
      const std::source_location& source               //
  ) {
    for (auto& logger : loggers) {
      logger->log(level, tag, exception, message, source);
    }
  }

  void log(                                                   //
      const Level level,                                      //
      const std::string_view tag,                             //
      const std::optional<std::exception>& exception,         //
      const std::function<const std::string_view()> message,  //
      const std::source_location& source                      //
  ) {
    for (auto& logger : loggers) {
      logger->log(level, tag, exception, message, source);
    }
  }

 private:
  std::array<std::unique_ptr<LoggerInterface>, N> loggers;
};

}  // namespace Util
}  // namespace Logger
}  // namespace DIG