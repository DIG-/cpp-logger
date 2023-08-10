#pragma once

#include <exception>
#include <functional>
#include <optional>
#include <source_location>
#include <string_view>

#include "level.hpp"

namespace DIG {
namespace Logger {

class LoggerInterface {
 public:
  const uint32_t magic_number = 0xFEFEEFEF;

  LoggerInterface(){};
  virtual ~LoggerInterface(){};

  virtual void log(                                    //
      const Level level,                               //
      const std::string_view tag,                      //
      const std::optional<std::exception>& exception,  //
      const std::string_view message,                  //
      const std::source_location& source               //
      ) = 0;

  virtual void log(                                           //
      const Level level,                                      //
      const std::string_view tag,                             //
      const std::optional<std::exception>& exception,         //
      const std::function<const std::string_view()> message,  //
      const std::source_location& source                      //
      ) = 0;
};

}  // namespace Logger
}  // namespace DIG
