#pragma once

#include <dig-logger/interface.hpp>
#include <dig-logger/printer/formatter.hpp>
#include <stdexcept>
#include <string>
#include <typeinfo>

class ForwardingString : public DIG::Logger::LoggerInterface {
 public:
  ForwardingString(const DIG::Logger::Level level, const std::string_view tag, const std::string_view message,
                   const std::optional<std::exception> exception, const std::source_location source, unsigned& count)
      : level(level), tag(tag), message(message), exception(exception), source(source), count(count){};
  ~ForwardingString(){};

  void log(                                            //
      const DIG::Logger::Level level,                  //
      const std::string_view tag,                      //
      const std::optional<std::exception>& exception,  //
      const std::string_view message,                  //
      const std::source_location& source               //
  ) {
    if (level != this->level) {
      throw std::logic_error(std::string("Forward log level is wrong\nExpected: ") +
                             std::string(DIG::Logger::Printer::Formatter::level_long(this->level)) +
                             std::string("\nReceived: ") + DIG::Logger::Printer::Formatter::level_long(level));
    }
    if (tag != this->tag) {
      throw std::logic_error(std::string("Forward log tag is wrong\nExpected: ") + std::string(this->tag) +
                             std::string("\nReceived: ") + std::string(tag));
    }
    if (exception.has_value() != this->exception.has_value()) {
      throw std::logic_error(
          std::string("Forward log exception is wrong\nExcepted: ") +
          std::string(this->exception.has_value() ? typeid(this->exception.value()).name() : "none") +
          std::string("\nReceived: ") +
          std::string(this->exception.has_value() ? typeid(this->exception.value()).name() : "none"));
    } else if (exception.has_value()) {
      if (typeid(exception.value()) != typeid(this->exception.value())) {
        throw std::logic_error(std::string("Forward log exception is wrong\nExcepted: ") +
                               std::string(typeid(this->exception.value()).name()) + std::string("\nReceived: ") +
                               std::string(typeid(this->exception.value()).name()));
      } else if (exception.value().what() != this->exception.value().what()) {
        throw std::logic_error(std::string("Forward log exception is wrong\nExcepted: ") +
                               std::string(this->exception.value().what()) + std::string("\nReceived: ") +
                               std::string(this->exception.value().what()));
      }
    }
    if (message != this->message) {
      throw std::logic_error(std::string("Forward log message is wrong\nExpected: ") + std::string(this->message) +
                             std::string("\nReceived: ") + std::string(message));
    }
    if (source.file_name() != this->source.file_name()) {
      throw std::logic_error(std::string("Forward log source is wrong\nExpected: ") +
                             std::string(this->source.file_name()) + std::string("\n Received: ") + source.file_name());
    } else if (source.line() != this->source.line()) {
      throw std::logic_error(std::string("Forward log source is wrong\nExpected line: ") +
                             std::to_string(this->source.line()) + std::string("\n Received line: ") +
                             std::to_string(source.line()));
    } else if (source.column() != this->source.column()) {
      throw std::logic_error(std::string("Forward log source is wrong\nExpected column: ") +
                             std::to_string(this->source.column()) + std::string("\n Received column: ") +
                             std::to_string(source.column()));
    }
    count++;
  }

  void log(                                                   //
      const DIG::Logger::Level level,                         //
      const std::string_view tag,                             //
      const std::optional<std::exception>& exception,         //
      const std::function<const std::string_view()> message,  //
      const std::source_location& source                      //
  ) {
    throw std::logic_error("Not expected to call message function method");
  }

 private:
  const DIG::Logger::Level level;
  const std::string_view tag;
  const std::string_view message;
  const std::optional<std::exception> exception;
  const std::source_location source;
  unsigned& count;
};

class ForwardingCallable : public DIG::Logger::LoggerInterface {
 public:
  ForwardingCallable(const DIG::Logger::Level level, const std::string_view tag, const std::string_view message,
                     const std::optional<std::exception> exception, const std::source_location source, unsigned& count)
      : level(level), tag(tag), message(message), exception(exception), source(source), count(count){};
  ~ForwardingCallable(){};

  void log(                                            //
      const DIG::Logger::Level level,                  //
      const std::string_view tag,                      //
      const std::optional<std::exception>& exception,  //
      const std::string_view message,                  //
      const std::source_location& source               //
  ) {
    throw std::logic_error("Not expected to call message string method");
  }

  void log(                                                   //
      const DIG::Logger::Level level,                         //
      const std::string_view tag,                             //
      const std::optional<std::exception>& exception,         //
      const std::function<const std::string_view()> message,  //
      const std::source_location& source                      //
  ) {
    if (level != this->level) {
      throw std::logic_error(std::string("Forward log level is wrong\nExpected: ") +
                             std::string(DIG::Logger::Printer::Formatter::level_long(this->level)) +
                             std::string("\nReceived: ") + DIG::Logger::Printer::Formatter::level_long(level));
    }
    if (tag != this->tag) {
      throw std::logic_error(std::string("Forward log tag is wrong\nExpected: ") + std::string(this->tag) +
                             std::string("\nReceived: ") + std::string(tag));
    }
    if (exception.has_value() != this->exception.has_value()) {
      throw std::logic_error(
          std::string("Forward log exception is wrong\nExcepted: ") +
          std::string(this->exception.has_value() ? typeid(this->exception.value()).name() : "none") +
          std::string("\nReceived: ") +
          std::string(this->exception.has_value() ? typeid(this->exception.value()).name() : "none"));
    } else if (exception.has_value()) {
      if (typeid(exception.value()) != typeid(this->exception.value())) {
        throw std::logic_error(std::string("Forward log exception is wrong\nExcepted: ") +
                               std::string(typeid(this->exception.value()).name()) + std::string("\nReceived: ") +
                               std::string(typeid(this->exception.value()).name()));
      } else if (exception.value().what() != this->exception.value().what()) {
        throw std::logic_error(std::string("Forward log exception is wrong\nExcepted: ") +
                               std::string(this->exception.value().what()) + std::string("\nReceived: ") +
                               std::string(this->exception.value().what()));
      }
    }
    if (message() != this->message) {
      throw std::logic_error(std::string("Forward log message is wrong\nExpected: ") + std::string(this->message) +
                             std::string("\nReceived: ") + std::string(message()));
    }
    if (source.file_name() != this->source.file_name()) {
      throw std::logic_error(std::string("Forward log source is wrong\nExpected: ") +
                             std::string(this->source.file_name()) + std::string("\n Received: ") + source.file_name());
    } else if (source.line() != this->source.line()) {
      throw std::logic_error(std::string("Forward log source is wrong\nExpected line: ") +
                             std::to_string(this->source.line()) + std::string("\n Received line: ") +
                             std::to_string(source.line()));
    } else if (source.column() != this->source.column()) {
      throw std::logic_error(std::string("Forward log source is wrong\nExpected column: ") +
                             std::to_string(this->source.column()) + std::string("\n Received column: ") +
                             std::to_string(source.column()));
    }
    count++;
  }

 private:
  const DIG::Logger::Level level;
  const std::string_view tag;
  const std::string_view message;
  const std::optional<std::exception> exception;
  const std::source_location source;
  unsigned& count;
};