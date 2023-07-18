#pragma once

#include "interface.hpp"
#include "logger.hpp"

namespace DIG {
namespace Logger {

template <typename T, typename std::enable_if_t<std::is_base_of_v<LoggerInterface, T>>* = nullptr>
Logger create(std::shared_ptr<T>& logger, const std::string_view tag) {
  return Logger(logger, tag);
}

template <typename T, typename std::enable_if_t<std::is_base_of_v<LoggerInterface, T>>* = nullptr>
Logger create(std::shared_ptr<T>&& logger, const std::string_view tag) {
  return Logger(logger, tag);
}

}  // namespace Logger
}  // namespace DIG