#pragma once

#include <array>
#include <dig-logger/interface.hpp>
#include <memory>
#include <stdexcept>
#include <string>

namespace DIG {
namespace Logger {
namespace Util {

template <std::size_t N>
class Union : public LoggerInterface {
  static_assert(N > 1, "Union is only available with more than one LoggerInterface");

 public:
  Union(std::array<std::unique_ptr<LoggerInterface>, N>& loggers) : loggers(std::move(loggers)) { check(); };
  Union(std::array<std::unique_ptr<LoggerInterface>, N>&& loggers) : loggers(std::move(loggers)) { check(); };

  template <class... Args>
  Union(Args&&... args) : loggers({std::move(args)...}) {
    check();
  };

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

  void check() {
    for (auto it = loggers.begin(); it != loggers.end(); it++) {
      if (it->get() == nullptr) [[unlikely]] {
        throw std::logic_error(                                 //
            std::string("LoggerInterface at position #") +        //
            std::to_string(std::distance(loggers.begin(), it)) +  //
            " is null!"                                           //
        );
      }
    }
  }
};

}  // namespace Util
}  // namespace Logger
}  // namespace DIG