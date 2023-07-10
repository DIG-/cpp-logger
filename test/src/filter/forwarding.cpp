#include <dig-logger/printer/formatter.hpp>
#include <dig-logger/util/filter.hpp>

#include "../common/forwarding.hpp"
#include "../common/random-string.hpp"

std::string message_of_function = random_string(32);

const std::string& create_message() { return message_of_function; }

using namespace DIG::Logger;

void test_level(const Level level) {
  auto tag = random_string(32);
  auto message = random_string(32);
  auto exception = std::optional(std::runtime_error(random_string(32)));
  auto source = std::source_location::current();
  unsigned count = 0;

  Util::Filter logger_string(std::make_unique<ForwardingString>(level, tag, message, exception, source, count),
                             Level::NONE);
  logger_string.log(level, tag, exception, message, source);
  if (count != 1) {
    throw std::logic_error(std::string("Log string not forwarded for level ") + Printer::Formatter::level_long(level));
  }

  count = 0;
  Util::Filter logger_callable(
      std::make_unique<ForwardingCallable>(level, tag, message_of_function, exception, source, count), Level::NONE);
  logger_callable.log(level, tag, exception, ::create_message, source);
  if (count != 1) {
    throw std::logic_error(std::string("Log callable not forwarded for level ") +
                           Printer::Formatter::level_long(level));
  }
}

int main(int argc, char** argv) {
  test_level(Level::NONE);
  test_level(Level::VERBOSE);
  test_level(Level::DEBUG);
  test_level(Level::INFORMATION);
  test_level(Level::WARNING);
  test_level(Level::ERROR);
  test_level(Level::ASSERT);
}