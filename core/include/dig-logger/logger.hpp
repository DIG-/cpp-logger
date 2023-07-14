#pragma once

#include <exception>
#include <functional>
#include <memory>
#include <optional>
#include <source_location>
#include <string_view>

#include "interface.hpp"
#include "level.hpp"

namespace DIG {
namespace Logger {

class Logger {
 public:
  template <typename T, typename std::enable_if_t<std::is_base_of_v<LoggerInterface, T>>* = nullptr>
  Logger(std::unique_ptr<T>& logger, const std::string_view tag) : logger(std::move(logger)), tag(tag){};

  template <typename T, typename std::enable_if_t<std::is_base_of_v<LoggerInterface, T>>* = nullptr>
  Logger(std::shared_ptr<T>& logger, const std::string_view tag) : logger(logger), tag(tag){};

  template <typename T, typename std::enable_if_t<std::is_base_of_v<LoggerInterface, T>>* = nullptr>
  Logger(std::shared_ptr<T>&& logger, const std::string_view tag) : logger(logger), tag(tag){};

  Logger(Logger&& other) : logger(other.logger), tag(other.tag){};
  ~Logger(){};

  using Message = const std::string_view;
  using Lambda = const std::function<Message()>;
  using Source = std::source_location;
  using Exception = std::exception;
  using OptException = std::optional<Exception>;

  //****************
  //  Assert Block
  //****************
  inline void assert(Message message, const Source source = Source::current()) {
    logger->log(Level::ASSERT, tag, OptException(), message, source);
  }
  inline void assert(Lambda message, const Source source = Source::current()) {
    logger->log(Level::ASSERT, tag, OptException(), message, source);
  }
  inline void assert(const Exception& exception, const Source source = Source::current()) {
    logger->log(Level::ASSERT, tag, OptException(exception), "", source);
  }
  inline void assert(const Exception& exception, Message message, const Source source = Source::current()) {
    logger->log(Level::ASSERT, tag, OptException(exception), message, source);
  }
  inline void assert(const Exception& exception, Lambda message, const Source source = Source::current()) {
    logger->log(Level::ASSERT, tag, OptException(exception), message, source);
  }

  //***************
  //  Error Block
  //***************
  inline void error(Message message, const Source source = Source::current()) {
    logger->log(Level::ERROR, tag, OptException(), message, source);
  }
  inline void error(Lambda message, const Source source = Source::current()) {
    logger->log(Level::ERROR, tag, OptException(), message, source);
  }
  inline void error(const Exception& exception, const Source source = Source::current()) {
    logger->log(Level::ERROR, tag, OptException(exception), "", source);
  }
  inline void error(const Exception& exception, Message message, const Source source = Source::current()) {
    logger->log(Level::ERROR, tag, OptException(exception), message, source);
  }
  inline void error(const Exception& exception, Lambda message, const Source source = Source::current()) {
    logger->log(Level::ERROR, tag, OptException(exception), message, source);
  }

  //*****************
  //  Warning Block
  //*****************
  inline void warning(Message message, const Source source = Source::current()) {
    logger->log(Level::WARNING, tag, OptException(), message, source);
  }
  inline void warning(Lambda message, const Source source = Source::current()) {
    logger->log(Level::WARNING, tag, OptException(), message, source);
  }
  inline void warning(const Exception& exception, const Source source = Source::current()) {
    logger->log(Level::WARNING, tag, OptException(exception), "", source);
  }
  inline void warning(const Exception& exception, Message message, const Source source = Source::current()) {
    logger->log(Level::WARNING, tag, OptException(exception), message, source);
  }
  inline void warning(const Exception& exception, Lambda message, const Source source = Source::current()) {
    logger->log(Level::WARNING, tag, OptException(exception), message, source);
  }

  //*********************
  //  Information Block
  //*********************
  inline void info(Message message, const Source source = Source::current()) {
    logger->log(Level::INFORMATION, tag, OptException(), message, source);
  }
  inline void info(Lambda message, const Source source = Source::current()) {
    logger->log(Level::INFORMATION, tag, OptException(), message, source);
  }
  inline void info(const Exception& exception, const Source source = Source::current()) {
    logger->log(Level::INFORMATION, tag, OptException(exception), "", source);
  }
  inline void info(const Exception& exception, Message message, const Source source = Source::current()) {
    logger->log(Level::INFORMATION, tag, OptException(exception), message, source);
  }
  inline void info(const Exception& exception, Lambda message, const Source source = Source::current()) {
    logger->log(Level::INFORMATION, tag, OptException(exception), message, source);
  }

  //***************
  //  Debug Block
  //***************
  inline void debug(Message message, const Source source = Source::current()) {
    logger->log(Level::DEBUG, tag, OptException(), message, source);
  }
  inline void debug(Lambda message, const Source source = Source::current()) {
    logger->log(Level::DEBUG, tag, OptException(), message, source);
  }
  inline void debug(const Exception& exception, const Source source = Source::current()) {
    logger->log(Level::DEBUG, tag, OptException(exception), "", source);
  }
  inline void debug(const Exception& exception, Message message, const Source source = Source::current()) {
    logger->log(Level::DEBUG, tag, OptException(exception), message, source);
  }
  inline void debug(const Exception& exception, Lambda message, const Source source = Source::current()) {
    logger->log(Level::DEBUG, tag, OptException(exception), message, source);
  }

  //*****************
  //  Verbose Block
  //*****************
  inline void verbose(Message message, const Source source = Source::current()) {
    logger->log(Level::VERBOSE, tag, OptException(), message, source);
  }
  inline void verbose(Lambda message, const Source source = Source::current()) {
    logger->log(Level::VERBOSE, tag, OptException(), message, source);
  }
  inline void verbose(const Exception& exception, const Source source = Source::current()) {
    logger->log(Level::VERBOSE, tag, OptException(exception), "", source);
  }
  inline void verbose(const Exception& exception, Message message, const Source source = Source::current()) {
    logger->log(Level::VERBOSE, tag, OptException(exception), message, source);
  }
  inline void verbose(const Exception& exception, Lambda message, const Source source = Source::current()) {
    logger->log(Level::VERBOSE, tag, OptException(exception), message, source);
  }

  //*********************
  //  Error Short Block
  //*********************
  inline void e(Message message, const Source source = Source::current()) {
    logger->log(Level::ERROR, tag, OptException(), message, source);
  }
  inline void e(Lambda message, const Source source = Source::current()) {
    logger->log(Level::ERROR, tag, OptException(), message, source);
  }
  inline void e(const Exception& exception, const Source source = Source::current()) {
    logger->log(Level::ERROR, tag, OptException(exception), "", source);
  }
  inline void e(const Exception& exception, Message message, const Source source = Source::current()) {
    logger->log(Level::ERROR, tag, OptException(exception), message, source);
  }
  inline void e(const Exception& exception, Lambda message, const Source source = Source::current()) {
    logger->log(Level::ERROR, tag, OptException(exception), message, source);
  }

  //***********************
  //  Warning Short Block
  //***********************
  inline void w(Message message, const Source source = Source::current()) {
    logger->log(Level::WARNING, tag, OptException(), message, source);
  }
  inline void w(Lambda message, const Source source = Source::current()) {
    logger->log(Level::WARNING, tag, OptException(), message, source);
  }
  inline void w(const Exception& exception, const Source source = Source::current()) {
    logger->log(Level::WARNING, tag, OptException(exception), "", source);
  }
  inline void w(const Exception& exception, Message message, const Source source = Source::current()) {
    logger->log(Level::WARNING, tag, OptException(exception), message, source);
  }
  inline void w(const Exception& exception, Lambda message, const Source source = Source::current()) {
    logger->log(Level::WARNING, tag, OptException(exception), message, source);
  }

  //***************************
  //  Information Short Block
  //***************************
  inline void i(Message message, const Source source = Source::current()) {
    logger->log(Level::INFORMATION, tag, OptException(), message, source);
  }
  inline void i(Lambda message, const Source source = Source::current()) {
    logger->log(Level::INFORMATION, tag, OptException(), message, source);
  }
  inline void i(const Exception& exception, const Source source = Source::current()) {
    logger->log(Level::INFORMATION, tag, OptException(exception), "", source);
  }
  inline void i(const Exception& exception, Message message, const Source source = Source::current()) {
    logger->log(Level::INFORMATION, tag, OptException(exception), message, source);
  }
  inline void i(const Exception& exception, Lambda message, const Source source = Source::current()) {
    logger->log(Level::INFORMATION, tag, OptException(exception), message, source);
  }

  //*********************
  //  Debug Short Block
  //*********************
  inline void d(Message message, const Source source = Source::current()) {
    logger->log(Level::DEBUG, tag, OptException(), message, source);
  }
  inline void d(Lambda message, const Source source = Source::current()) {
    logger->log(Level::DEBUG, tag, OptException(), message, source);
  }
  inline void d(const Exception& exception, const Source source = Source::current()) {
    logger->log(Level::DEBUG, tag, OptException(exception), "", source);
  }
  inline void d(const Exception& exception, Message message, const Source source = Source::current()) {
    logger->log(Level::DEBUG, tag, OptException(exception), message, source);
  }
  inline void d(const Exception& exception, Lambda message, const Source source = Source::current()) {
    logger->log(Level::DEBUG, tag, OptException(exception), message, source);
  }

  //***********************
  //  Verbose Short Block
  //***********************
  inline void v(Message message, const Source source = Source::current()) {
    logger->log(Level::VERBOSE, tag, OptException(), message, source);
  }
  inline void v(Lambda message, const Source source = Source::current()) {
    logger->log(Level::VERBOSE, tag, OptException(), message, source);
  }
  inline void v(const Exception& exception, const Source source = Source::current()) {
    logger->log(Level::VERBOSE, tag, OptException(exception), "", source);
  }
  inline void v(const Exception& exception, Message message, const Source source = Source::current()) {
    logger->log(Level::VERBOSE, tag, OptException(exception), message, source);
  }
  inline void v(const Exception& exception, Lambda message, const Source source = Source::current()) {
    logger->log(Level::VERBOSE, tag, OptException(exception), message, source);
  }

 private:
  const std::shared_ptr<LoggerInterface> logger;
  const std::string_view tag;
};

}  // namespace Logger
}  // namespace DIG