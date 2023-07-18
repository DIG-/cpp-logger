#pragma once

#include <exception>
#include <functional>
#include <memory>
#include <source_location>
#include <string_view>

namespace DIG {
namespace Logger {

class Logger {
 public:
  Logger(std::shared_ptr<void>& logger, const std::string_view tag) : logger(logger), tag(tag) { check(); };
  Logger(std::shared_ptr<void>&& logger, const std::string_view tag) : logger(logger), tag(tag) { check(); };

  Logger(Logger& other) noexcept : logger(other.logger), tag(other.tag){};
  Logger(Logger& other, const std::string_view tag) noexcept : logger(other.logger), tag(tag){};
  Logger(Logger&& other) noexcept : logger(other.logger), tag(other.tag){};
  ~Logger(){};

  using Message = const std::string_view;
  using Lambda = const std::function<Message()>;
  using Source = std::source_location;
  using Exception = std::exception;

  //****************
  //  Assert Block
  //****************
  void assert(Message message, const Source source = Source::current());
  void assert(Lambda message, const Source source = Source::current());
  void assert(const Exception& exception, const Source source = Source::current());
  void assert(const Exception& exception, Message message, const Source source = Source::current());
  void assert(const Exception& exception, Lambda message, const Source source = Source::current());

  //***************
  //  Error Block
  //***************
  void error(Message message, const Source source = Source::current());
  void error(Lambda message, const Source source = Source::current());
  void error(const Exception& exception, const Source source = Source::current());
  void error(const Exception& exception, Message message, const Source source = Source::current());
  void error(const Exception& exception, Lambda message, const Source source = Source::current());

  //*****************
  //  Warning Block
  //*****************
  void warning(Message message, const Source source = Source::current());
  void warning(Lambda message, const Source source = Source::current());
  void warning(const Exception& exception, const Source source = Source::current());
  void warning(const Exception& exception, Message message, const Source source = Source::current());
  void warning(const Exception& exception, Lambda message, const Source source = Source::current());

  //*********************
  //  Information Block
  //*********************
  void info(Message message, const Source source = Source::current());
  void info(Lambda message, const Source source = Source::current());
  void info(const Exception& exception, const Source source = Source::current());
  void info(const Exception& exception, Message message, const Source source = Source::current());
  void info(const Exception& exception, Lambda message, const Source source = Source::current());

  //***************
  //  Debug Block
  //***************
  void debug(Message message, const Source source = Source::current());
  void debug(Lambda message, const Source source = Source::current());
  void debug(const Exception& exception, const Source source = Source::current());
  void debug(const Exception& exception, Message message, const Source source = Source::current());
  void debug(const Exception& exception, Lambda message, const Source source = Source::current());

  //*****************
  //  Verbose Block
  //*****************
  void verbose(Message message, const Source source = Source::current());
  void verbose(Lambda message, const Source source = Source::current());
  void verbose(const Exception& exception, const Source source = Source::current());
  void verbose(const Exception& exception, Message message, const Source source = Source::current());
  void verbose(const Exception& exception, Lambda message, const Source source = Source::current());

  //*********************
  //  Error Short Block
  //*********************
  void e(Message message, const Source source = Source::current());
  void e(Lambda message, const Source source = Source::current());
  void e(const Exception& exception, const Source source = Source::current());
  void e(const Exception& exception, Message message, const Source source = Source::current());
  void e(const Exception& exception, Lambda message, const Source source = Source::current());

  //***********************
  //  Warning Short Block
  //***********************
  void w(Message message, const Source source = Source::current());
  void w(Lambda message, const Source source = Source::current());
  void w(const Exception& exception, const Source source = Source::current());
  void w(const Exception& exception, Message message, const Source source = Source::current());
  void w(const Exception& exception, Lambda message, const Source source = Source::current());

  //***************************
  //  Information Short Block
  //***************************
  void i(Message message, const Source source = Source::current());
  void i(Lambda message, const Source source = Source::current());
  void i(const Exception& exception, const Source source = Source::current());
  void i(const Exception& exception, Message message, const Source source = Source::current());
  void i(const Exception& exception, Lambda message, const Source source = Source::current());

  //*********************
  //  Debug Short Block
  //*********************
  void d(Message message, const Source source = Source::current());
  void d(Lambda message, const Source source = Source::current());
  void d(const Exception& exception, const Source source = Source::current());
  void d(const Exception& exception, Message message, const Source source = Source::current());
  void d(const Exception& exception, Lambda message, const Source source = Source::current());

  //***********************
  //  Verbose Short Block
  //***********************
  void v(Message message, const Source source = Source::current());
  void v(Lambda message, const Source source = Source::current());
  void v(const Exception& exception, const Source source = Source::current());
  void v(const Exception& exception, Message message, const Source source = Source::current());
  void v(const Exception& exception, Lambda message, const Source source = Source::current());

 private:
  void check();
  const std::shared_ptr<void> logger;
  const std::string_view tag;
};

}  // namespace Logger
}  // namespace DIG