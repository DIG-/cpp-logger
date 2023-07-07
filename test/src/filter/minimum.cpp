#include <dig-logger/printer/formatter.hpp>
#include <dig-logger/util/filter.hpp>
#include <stdexcept>

using namespace DIG::Logger;

class MinimunDetection : public LoggerInterface {
 public:
  MinimunDetection(const Level minimum) : minimum(minimum){};
  ~MinimunDetection(){};

  void log(                                            //
      const Level level,                               //
      const std::string_view tag,                      //
      const std::optional<std::exception>& exception,  //
      const std::string_view message,                  //
      const std::source_location& source               //
  ) {
    if (level < minimum) {
      throw std::logic_error(std::string("Log must be filtered.. Received=") +
                             std::string(Printer::Formatter::level_long(level)) + std::string("; Minimum=") +
                             std::string(Printer::Formatter::level_long(minimum)));
    }
  }

  void log(                                                   //
      const Level level,                                      //
      const std::string_view tag,                             //
      const std::optional<std::exception>& exception,         //
      const std::function<const std::string_view()> message,  //
      const std::source_location& source                      //
  ) {
    if (level < minimum) {
      throw std::logic_error(std::string("Log must be filtered.. Received=") +
                             std::string(Printer::Formatter::level_long(level)) + std::string("; Minimum=") +
                             std::string(Printer::Formatter::level_long(minimum)));
    }
  }

 private:
  const Level minimum;
};

std::string generate_message() { return "empty"; }

void dispatch_all_messages(LoggerInterface& logger) {
  auto exception = std::optional<std::exception>();
  logger.log(Level::VERBOSE, "tag", exception, "message", std::source_location::current());
  logger.log(Level::VERBOSE, "tag", exception, ::generate_message, std::source_location::current());
  logger.log(Level::DEBUG, "tag", exception, "message", std::source_location::current());
  logger.log(Level::DEBUG, "tag", exception, ::generate_message, std::source_location::current());
  logger.log(Level::INFORMATION, "tag", exception, "message", std::source_location::current());
  logger.log(Level::INFORMATION, "tag", exception, ::generate_message, std::source_location::current());
  logger.log(Level::WARNING, "tag", exception, "message", std::source_location::current());
  logger.log(Level::WARNING, "tag", exception, ::generate_message, std::source_location::current());
  logger.log(Level::ERROR, "tag", exception, "message", std::source_location::current());
  logger.log(Level::ERROR, "tag", exception, ::generate_message, std::source_location::current());
  logger.log(Level::ASSERT, "tag", exception, "message", std::source_location::current());
  logger.log(Level::ASSERT, "tag", exception, ::generate_message, std::source_location::current());
}

int main(int argc, char** argv) {
  auto minimum_none = Util::Filter(std::make_unique<MinimunDetection>(Level::NONE), Level::NONE);
  dispatch_all_messages(minimum_none);
  auto minimum_debug = Util::Filter(std::make_unique<MinimunDetection>(Level::DEBUG), Level::DEBUG);
  dispatch_all_messages(minimum_debug);
  auto minimum_information = Util::Filter(std::make_unique<MinimunDetection>(Level::INFORMATION), Level::INFORMATION);
  dispatch_all_messages(minimum_information);
  auto minimum_warning = Util::Filter(std::make_unique<MinimunDetection>(Level::WARNING), Level::WARNING);
  dispatch_all_messages(minimum_warning);
  auto minimum_error = Util::Filter(std::make_unique<MinimunDetection>(Level::ERROR), Level::ERROR);
  dispatch_all_messages(minimum_error);
  auto minimum_assert = Util::Filter(std::make_unique<MinimunDetection>(Level::ASSERT), Level::ASSERT);
  dispatch_all_messages(minimum_assert);

  return 0;
}