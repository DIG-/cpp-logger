#pragma once

#include <dig-logger/interface.hpp>
#include <dig-logger/printer/formatter.hpp>
#include <sstream>
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
    /*
    if (level != this->level) {
      std::stringstream ss;
      ss << "Forward log level is wrong"                              //
         << "\nExpected: "                                            //
         << DIG::Logger::Printer::Formatter::level_long(this->level)  //
         << "\nReceived: "                                            //
         << DIG::Logger::Printer::Formatter::level_long(level);
      throw std::logic_error(ss.str());
    }
    if (tag != this->tag) {
      std::stringstream ss;
      ss << "Forward log tag is wrong"  //
         << "\nExpected: "              //
         << this->tag                   //
         << "\nReceived: "              //
         << tag;
      throw std::logic_error(ss.str());
    }
    if (exception.has_value() != this->exception.has_value()) {
      std::stringstream ss;
      ss << "Forward log exception is wrong"                                                 //
         << "\nExpected: "                                                                   //
         << (this->exception.has_value() ? typeid(this->exception.value()).name() : "none")  //
         << "\nReceived: "                                                                   //
         << (exception.has_value() ? typeid(exception.value()).name() : "none");
      throw std::logic_error(ss.str());
    } else if (exception.has_value()) {
      if (typeid(exception.value()) != typeid(this->exception.value())) {
        std::stringstream ss;
        ss << "Forward log exception is wrong"        //
           << "\nExpected: "                          //
           << typeid(this->exception.value()).name()  //
           << "\nReceived: "                          //
           << typeid(exception.value()).name();
        throw std::logic_error(ss.str());
      } else if (exception.value().what() != this->exception.value().what()) {
        std::stringstream ss;
        ss << "Forward log exception is wrong"  //
           << "\nExpected: "                    //
           << this->exception.value().what()    //
           << "\nReceived: "                    //
           << exception.value().what();
        throw std::logic_error(ss.str());
      }
    }
    if (message != this->message) {
      std::stringstream ss;
      ss << "Forward log message is wrong"  //
         << "\nExpected: "                  //
         << this->message                   //
         << "\nReceived: "                  //
         << message;
      throw std::logic_error(ss.str());
    }
    if (source.file_name() != this->source.file_name()) {
      std::stringstream ss;
      ss << "Forward log source is wrong"  //
         << "\nExpected: "                 //
         << this->source.file_name()       //
         << "\nReceived: "                 //
         << source.file_name();
      throw std::logic_error(ss.str());
    } else if (source.line() != this->source.line()) {
      std::stringstream ss;
      ss << "Forward log source is wrong"  //
         << "\nExpected line: "            //
         << this->source.line()            //
         << "\nReceived line: "            //
         << source.line();
      throw std::logic_error(ss.str());
    } else if (source.column() != this->source.column()) {
      std::stringstream ss;
      ss << "Forward log source is wrong"  //
         << "\nExpected column: "          //
         << this->source.line()            //
         << "\nReceived column: "          //
         << source.line();
      throw std::logic_error(ss.str());
    }
    */
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
    /*
    if (level != this->level) {
      std::stringstream ss;
      ss << "Forward log level is wrong"                              //
         << "\nExpected: "                                            //
         << DIG::Logger::Printer::Formatter::level_long(this->level)  //
         << "\nReceived: "                                            //
         << DIG::Logger::Printer::Formatter::level_long(level);
      throw std::logic_error(ss.str());
    }
    if (tag != this->tag) {
      std::stringstream ss;
      ss << "Forward log tag is wrong"  //
         << "\nExpected: "              //
         << this->tag                   //
         << "\nReceived: "              //
         << tag;
      throw std::logic_error(ss.str());
    }
    if (exception.has_value() != this->exception.has_value()) {
      std::stringstream ss;
      ss << "Forward log exception is wrong"                                                 //
         << "\nExpected: "                                                                   //
         << (this->exception.has_value() ? typeid(this->exception.value()).name() : "none")  //
         << "\nReceived: "                                                                   //
         << (exception.has_value() ? typeid(exception.value()).name() : "none");
      throw std::logic_error(ss.str());
    } else if (exception.has_value()) {
      if (typeid(exception.value()) != typeid(this->exception.value())) {
        std::stringstream ss;
        ss << "Forward log exception is wrong"        //
           << "\nExpected: "                          //
           << typeid(this->exception.value()).name()  //
           << "\nReceived: "                          //
           << typeid(exception.value()).name();
        throw std::logic_error(ss.str());
      } else if (exception.value().what() != this->exception.value().what()) {
        std::stringstream ss;
        ss << "Forward log exception is wrong"  //
           << "\nExpected: "                    //
           << this->exception.value().what()    //
           << "\nReceived: "                    //
           << exception.value().what();
        throw std::logic_error(ss.str());
      }
    }
    if (message() != this->message) {
      std::stringstream ss;
      ss << "Forward log message is wrong"  //
         << "\nExpected: "                  //
         << this->message                   //
         << "\nReceived: "                  //
         << message();
      throw std::logic_error(ss.str());
    }
    if (source.file_name() != this->source.file_name()) {
      std::stringstream ss;
      ss << "Forward log source is wrong"  //
         << "\nExpected: "                 //
         << this->source.file_name()       //
         << "\nReceived: "                 //
         << source.file_name();
      throw std::logic_error(ss.str());
    } else if (source.line() != this->source.line()) {
      std::stringstream ss;
      ss << "Forward log source is wrong"  //
         << "\nExpected line: "            //
         << this->source.line()            //
         << "\nReceived line: "            //
         << source.line();
      throw std::logic_error(ss.str());
    } else if (source.column() != this->source.column()) {
      std::stringstream ss;
      ss << "Forward log source is wrong"  //
         << "\nExpected column: "          //
         << this->source.line()            //
         << "\nReceived column: "          //
         << source.line();
      throw std::logic_error(ss.str());
    }
    */
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