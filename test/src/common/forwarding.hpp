#pragma once

#include <dig-logger/interface.hpp>
#include <stdexcept>
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
      throw std::logic_error("Forward log level is wrong");
    }
    if (tag != this->tag) {
      throw std::logic_error("Forward log tag is wrong");
    }
    if (exception.has_value() != this->exception.has_value() &&
        (exception.has_value() && typeid(exception.value()) != typeid(this->exception.value()) &&
         exception.value().what() != this->exception.value().what())) {
      throw std::logic_error("Forward log exception is wrong");
    }
    if (message != this->message) {
      throw std::logic_error("Forward log message is wrong");
    }
    if (source.file_name() != this->source.file_name() && source.line() != this->source.line() &&
        source.column() != this->source.column()) {
      throw std::logic_error("Forward log source is wrong");
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
      throw std::logic_error("Forward log level is wrong");
    }
    if (tag != this->tag) {
      throw std::logic_error("Forward log tag is wrong");
    }
    if (exception.has_value() != this->exception.has_value() &&
        (exception.has_value() && typeid(exception.value()) != typeid(this->exception.value()) &&
         exception.value().what() != this->exception.value().what())) {
      throw std::logic_error("Forward log exception is wrong");
    }
    if (message() != this->message) {
      throw std::logic_error("Forward log message is wrong");
    }
    if (source.file_name() != this->source.file_name() && source.line() != this->source.line() &&
        source.column() != this->source.column()) {
      throw std::logic_error("Forward log source is wrong");
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