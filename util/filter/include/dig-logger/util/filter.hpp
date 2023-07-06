#pragma once

#include <dig-logger/interface.hpp>
#include <memory>

namespace DIG {
namespace Logger {
namespace Util {

class Filter : public LoggerInterface {
 public:
  template <typename T, typename std::enable_if_t<std::is_base_of_v<LoggerInterface, T>>* = nullptr>
  Filter(std::unique_ptr<T>& parent, const Level minimum, const Level maximum = Level::ASSERT)
      : parent(std::move(parent)), minimum(minimum), maximum(maximum) {
    check();
  };

  template <typename T, typename std::enable_if_t<std::is_base_of_v<LoggerInterface, T>>* = nullptr>
  Filter(std::unique_ptr<T>&& parent, const Level minimum, const Level maximum = Level::ASSERT)
      : parent(std::move(parent)), minimum(minimum), maximum(maximum) {
    check();
  };

  ~Filter(){};

  void log(                                            //
      const Level level,                               //
      const std::string_view tag,                      //
      const std::optional<std::exception>& exception,  //
      const std::string_view message,                  //
      const std::source_location& source               //
  );

  void log(                                                   //
      const Level level,                                      //
      const std::string_view tag,                             //
      const std::optional<std::exception>& exception,         //
      const std::function<const std::string_view()> message,  //
      const std::source_location& source                      //
  );

 private:
  const std::unique_ptr<LoggerInterface> parent;
  const Level minimum;
  const Level maximum;

  void check();
};

}  // namespace Util
}  // namespace Logger
}  // namespace DIG