#include "dig-logger/logger.hpp"

#include <optional>
#include <stdexcept>

#include "dig-logger/interface.hpp"
#include "dig-logger/level.hpp"

namespace DIG {
namespace Logger {

using OptionalException = std::optional<Logger::Exception>;
const char* empty_str = "";
const std::string_view empty(empty_str);

void Logger::check() {
  if (logger.get() == nullptr) [[unlikely]] {
    throw std::logic_error("Can not initialize Logger with null");
  }
  if (static_cast<LoggerInterface*>(logger.get()) == nullptr) [[unlikely]] {
    throw std::logic_error("Unable to cast logger as LoggerInterface");
  }
}

LoggerInterface& cast(std::shared_ptr<void> pointer) { return *static_cast<LoggerInterface*>(pointer.get()); }

//****************
//  Assert Block
//****************
void Logger::assert(Logger::Message message, const Logger::Source source) {
  cast(logger).log(Level::ASSERT, tag, OptionalException(), message, source);
}
void Logger::assert(Logger::Lambda message, const Logger::Source source) {
  cast(logger).log(Level::ASSERT, tag, OptionalException(), message, source);
}
void Logger::assert(const Logger::Exception& exception, const Logger::Source source) {
  cast(logger).log(Level::ASSERT, tag, OptionalException(exception), empty, source);
}
void Logger::assert(const Logger::Exception& exception, Logger::Message message, const Logger::Source source) {
  cast(logger).log(Level::ASSERT, tag, OptionalException(exception), message, source);
}
void Logger::assert(const Logger::Exception& exception, Logger::Lambda message, const Logger::Source source) {
  cast(logger).log(Level::ASSERT, tag, OptionalException(exception), message, source);
}

//***************
//  Error Block
//***************
void Logger::error(Logger::Message message, const Logger::Source source) {
  cast(logger).log(Level::ERROR, tag, OptionalException(), message, source);
}
void Logger::error(Logger::Lambda message, const Logger::Source source) {
  cast(logger).log(Level::ERROR, tag, OptionalException(), message, source);
}
void Logger::error(const Logger::Exception& exception, const Logger::Source source) {
  cast(logger).log(Level::ERROR, tag, OptionalException(exception), empty, source);
}
void Logger::error(const Logger::Exception& exception, Logger::Message message, const Logger::Source source) {
  cast(logger).log(Level::ERROR, tag, OptionalException(exception), message, source);
}
void Logger::error(const Logger::Exception& exception, Logger::Lambda message, const Logger::Source source) {
  cast(logger).log(Level::ERROR, tag, OptionalException(exception), message, source);
}

//*****************
//  Warning Block
//*****************
void Logger::warning(Logger::Message message, const Logger::Source source) {
  cast(logger).log(Level::WARNING, tag, OptionalException(), message, source);
}
void Logger::warning(Logger::Lambda message, const Logger::Source source) {
  cast(logger).log(Level::WARNING, tag, OptionalException(), message, source);
}
void Logger::warning(const Logger::Exception& exception, const Logger::Source source) {
  cast(logger).log(Level::WARNING, tag, OptionalException(exception), empty, source);
}
void Logger::warning(const Logger::Exception& exception, Logger::Message message, const Logger::Source source) {
  cast(logger).log(Level::WARNING, tag, OptionalException(exception), message, source);
}
void Logger::warning(const Logger::Exception& exception, Logger::Lambda message, const Logger::Source source) {
  cast(logger).log(Level::WARNING, tag, OptionalException(exception), message, source);
}

//*********************
//  Information Block
//*********************
void Logger::info(Logger::Message message, const Logger::Source source) {
  cast(logger).log(Level::INFORMATION, tag, OptionalException(), message, source);
}
void Logger::info(Logger::Lambda message, const Logger::Source source) {
  cast(logger).log(Level::INFORMATION, tag, OptionalException(), message, source);
}
void Logger::info(const Logger::Exception& exception, const Logger::Source source) {
  cast(logger).log(Level::INFORMATION, tag, OptionalException(exception), empty, source);
}
void Logger::info(const Logger::Exception& exception, Logger::Message message, const Logger::Source source) {
  cast(logger).log(Level::INFORMATION, tag, OptionalException(exception), message, source);
}
void Logger::info(const Logger::Exception& exception, Logger::Lambda message, const Logger::Source source) {
  cast(logger).log(Level::INFORMATION, tag, OptionalException(exception), message, source);
}

//***************
//  Debug Block
//***************
void Logger::debug(Logger::Message message, const Logger::Source source) {
  cast(logger).log(Level::DEBUG, tag, OptionalException(), message, source);
}
void Logger::debug(Logger::Lambda message, const Logger::Source source) {
  cast(logger).log(Level::DEBUG, tag, OptionalException(), message, source);
}
void Logger::debug(const Logger::Exception& exception, const Logger::Source source) {
  cast(logger).log(Level::DEBUG, tag, OptionalException(exception), empty, source);
}
void Logger::debug(const Logger::Exception& exception, Logger::Message message, const Logger::Source source) {
  cast(logger).log(Level::DEBUG, tag, OptionalException(exception), message, source);
}
void Logger::debug(const Logger::Exception& exception, Logger::Lambda message, const Logger::Source source) {
  cast(logger).log(Level::DEBUG, tag, OptionalException(exception), message, source);
}

//*****************
//  Verbose Block
//*****************
void Logger::verbose(Logger::Message message, const Logger::Source source) {
  cast(logger).log(Level::VERBOSE, tag, OptionalException(), message, source);
}
void Logger::verbose(Logger::Lambda message, const Logger::Source source) {
  cast(logger).log(Level::VERBOSE, tag, OptionalException(), message, source);
}
void Logger::verbose(const Logger::Exception& exception, const Logger::Source source) {
  cast(logger).log(Level::VERBOSE, tag, OptionalException(exception), empty, source);
}
void Logger::verbose(const Logger::Exception& exception, Logger::Message message, const Logger::Source source) {
  cast(logger).log(Level::VERBOSE, tag, OptionalException(exception), message, source);
}
void Logger::verbose(const Logger::Exception& exception, Logger::Lambda message, const Logger::Source source) {
  cast(logger).log(Level::VERBOSE, tag, OptionalException(exception), message, source);
}

//*********************
//  Error Short Block
//*********************
void Logger::e(Logger::Message message, const Logger::Source source) { error(message, source); }
void Logger::e(Logger::Lambda message, const Logger::Source source) { error(message, source); }
void Logger::e(const Logger::Exception& exception, const Logger::Source source) { error(exception, source); }
void Logger::e(const Logger::Exception& exception, Logger::Message message, const Logger::Source source) {
  error(exception, message, source);
}
void Logger::e(const Logger::Exception& exception, Logger::Lambda message, const Logger::Source source) {
  error(exception, message, source);
}

//***********************
//  Warning Short Block
//***********************
void Logger::w(Logger::Message message, const Logger::Source source) { warning(message, source); }
void Logger::w(Logger::Lambda message, const Logger::Source source) { warning(message, source); }
void Logger::w(const Logger::Exception& exception, const Logger::Source source) { warning(exception, source); }
void Logger::w(const Logger::Exception& exception, Logger::Message message, const Logger::Source source) {
  warning(exception, message, source);
}
void Logger::w(const Logger::Exception& exception, Logger::Lambda message, const Logger::Source source) {
  warning(exception, message, source);
}

//***************************
//  Information Short Block
//***************************
void Logger::i(Logger::Message message, const Logger::Source source) { info(message, source); }
void Logger::i(Logger::Lambda message, const Logger::Source source) { info(message, source); }
void Logger::i(const Logger::Exception& exception, const Logger::Source source) { info(exception, source); }
void Logger::i(const Logger::Exception& exception, Logger::Message message, const Logger::Source source) {
  info(exception, message, source);
}
void Logger::i(const Logger::Exception& exception, Logger::Lambda message, const Logger::Source source) {
  info(exception, message, source);
}

//*********************
//  Debug Short Block
//*********************
void Logger::d(Logger::Message message, const Logger::Source source) { debug(message, source); }
void Logger::d(Logger::Lambda message, const Logger::Source source) { debug(message, source); }
void Logger::d(const Logger::Exception& exception, const Logger::Source source) { debug(exception, source); }
void Logger::d(const Logger::Exception& exception, Logger::Message message, const Logger::Source source) {
  debug(exception, message, source);
}
void Logger::d(const Logger::Exception& exception, Logger::Lambda message, const Logger::Source source) {
  debug(exception, message, source);
}

//***********************
//  Verbose Short Block
//***********************
void Logger::v(Logger::Message message, const Logger::Source source) { verbose(message, source); }
void Logger::v(Logger::Lambda message, const Logger::Source source) { verbose(message, source); }
void Logger::v(const Logger::Exception& exception, const Logger::Source source) { verbose(exception, source); }
void Logger::v(const Logger::Exception& exception, Logger::Message message, const Logger::Source source) {
  verbose(exception, message, source);
}
void Logger::v(const Logger::Exception& exception, Logger::Lambda message, const Logger::Source source) {
  verbose(exception, message, source);
}

}  // namespace Logger
}  // namespace DIG