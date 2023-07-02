#pragma once

#include <dig-logger/interface.hpp>
#include <memory>

namespace DIG {
namespace Logger {
namespace Util {

class Filter : public LoggerInterface {
 public:
  Filter(std::unique_ptr<LoggerInterface> parent, const Level& minimum, const Level& maximum = Level::ASSERT)
      : parent(std::move(parent)), minimum(minimum), maximum(maximum){};
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
};

}  // namespace Util
}  // namespace Logger
}  // namespace DIG