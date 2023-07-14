#include <dig-logger/logger.hpp>
#include <iostream>
#include <stdexcept>

#include "../common/forwarding.hpp"
#include "../common/random-string.hpp"

using namespace DIG::Logger;

std::string message_of_function = random_string(32);

const std::string& create_message() { return message_of_function; }

#define TEST(LEVEL, LONG, SHORT)                                                                                      \
  {                                                                                                                   \
    count = 0;                                                                                                        \
    std::cout << "Testing " #LONG " pure message\n";                                                                  \
    Logger log(std::make_shared<ForwardingString>(LEVEL, tag, message, exception_empty, source, count), tag);         \
    log.LONG(message, source);                                                                                        \
    log.SHORT(message, source);                                                                                       \
    if (count != 2) {                                                                                                 \
      throw std::logic_error("Failed to propagate " #LONG " log pure message");                                       \
    }                                                                                                                 \
  }                                                                                                                   \
  {                                                                                                                   \
    count = 0;                                                                                                        \
    std::cout << "Testing " #LONG " message and exception\n";                                                         \
    Logger log(std::make_shared<ForwardingString>(LEVEL, tag, message, exception_fill, source, count), tag);          \
    log.LONG(exception, message, source);                                                                             \
    log.SHORT(exception, message, source);                                                                            \
    if (count != 2) {                                                                                                 \
      throw std::logic_error("Failed to propagate " #LONG " log message and exception");                              \
    }                                                                                                                 \
  }                                                                                                                   \
  {                                                                                                                   \
    count = 0;                                                                                                        \
    std::cout << "Testing " #LONG " pure message callable\n";                                                         \
    Logger log(std::make_shared<ForwardingCallable>(LEVEL, tag, message_of_function, exception_empty, source, count), \
               tag);                                                                                                  \
    log.LONG(::create_message, source);                                                                               \
    log.SHORT(::create_message, source);                                                                              \
    if (count != 2) {                                                                                                 \
      throw std::logic_error("Failed to propagate " #LONG " log pure message callable");                              \
    }                                                                                                                 \
  }                                                                                                                   \
  {                                                                                                                   \
    count = 0;                                                                                                        \
    std::cout << "Testing " #LONG " message callable and exception\n";                                                \
    Logger log(std::make_shared<ForwardingCallable>(LEVEL, tag, message_of_function, exception_fill, source, count),  \
               tag);                                                                                                  \
    log.LONG(exception, ::create_message, source);                                                                    \
    log.SHORT(exception, ::create_message, source);                                                                   \
    if (count != 2) {                                                                                                 \
      throw std::logic_error("Failed to propagate " #LONG " log message callable and exception");                     \
    }                                                                                                                 \
  }                                                                                                                   \
  {                                                                                                                   \
    count = 0;                                                                                                        \
    std::cout << "Testing " #LONG " pure exception\n";                                                                \
    Logger log(std::make_shared<ForwardingString>(LEVEL, tag, "", exception_fill, source, count), tag);               \
    log.LONG(exception, source);                                                                                      \
    log.SHORT(exception, source);                                                                                     \
    if (count != 2) {                                                                                                 \
      throw std::logic_error("Failed to propagate " #LONG " log pure exception");                                     \
    }                                                                                                                 \
  }

int main(int argc, char** argv) {
  auto tag = random_string(32);
  auto message = random_string(32);
  auto exception = std::runtime_error(random_string(32));
  std::optional<std::exception> exception_fill(exception);
  std::optional<std::exception> exception_empty;
  auto source = std::source_location::current();
  unsigned count = 0;

  TEST(Level::VERBOSE, verbose, v)
  TEST(Level::DEBUG, debug, d)
  TEST(Level::INFORMATION, info, i)
  TEST(Level::WARNING, warning, w)
  TEST(Level::ERROR, error, e)
  TEST(Level::ASSERT, assert, assert)
  std::cout << "Success" << std::endl;
  return 0;
}