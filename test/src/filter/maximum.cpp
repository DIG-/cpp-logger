#include <dig-logger/printer/formatter.hpp>
#include <dig-logger/util/filter.hpp>
#include <stdexcept>

using namespace DIG::Logger;

class MaximumDetection : public LoggerInterface {
 public:
  MaximumDetection(const Level maximum) : maximum(maximum){};
  ~MaximumDetection(){};

  void log(                                            //
      const Level level,                               //
      const std::string_view tag,                      //
      const std::optional<std::exception>& exception,  //
      const std::string_view message,                  //
      const std::source_location& source               //
  ) {
    if (level > maximum) {
      throw std::logic_error(std::string("Log must be filtered.. Received=") +
                             std::string(Printer::Formatter::level_long(level)) + std::string("; Maximum=") +
                             std::string(Printer::Formatter::level_long(maximum)));
    }
  }

  void log(                                                   //
      const Level level,                                      //
      const std::string_view tag,                             //
      const std::optional<std::exception>& exception,         //
      const std::function<const std::string_view()> message,  //
      const std::source_location& source                      //
  ) {
    if (level > maximum) {
      throw std::logic_error(std::string("Log must be filtered.. Received=") +
                             std::string(Printer::Formatter::level_long(level)) + std::string("; Maximum=") +
                             std::string(Printer::Formatter::level_long(maximum)));
    }
  }

 private:
  const Level maximum;
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
  auto maximum_none = Util::Filter(std::make_unique<MaximumDetection>(Level::NONE), Level::NONE, Level::NONE);
  dispatch_all_messages(maximum_none);
  auto maximum_debug = Util::Filter(std::make_unique<MaximumDetection>(Level::DEBUG), Level::NONE, Level::DEBUG);
  dispatch_all_messages(maximum_debug);
  auto maximum_information =
      Util::Filter(std::make_unique<MaximumDetection>(Level::INFORMATION), Level::NONE, Level::INFORMATION);
  dispatch_all_messages(maximum_information);
  auto maximum_warning = Util::Filter(std::make_unique<MaximumDetection>(Level::WARNING), Level::NONE, Level::WARNING);
  dispatch_all_messages(maximum_warning);
  auto maximum_error = Util::Filter(std::make_unique<MaximumDetection>(Level::ERROR), Level::NONE, Level::ERROR);
  dispatch_all_messages(maximum_error);
  auto maximum_assert = Util::Filter(std::make_unique<MaximumDetection>(Level::ASSERT), Level::NONE, Level::ASSERT);
  dispatch_all_messages(maximum_assert);

  return 0;
}