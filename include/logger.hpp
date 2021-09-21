#ifndef _DIG_LOGGER_HPP_
#define _DIG_LOGGER_HPP_ 1

#if defined(DIG_LOGGER_STATIC) || !(defined(_MSC_VER) || defined(_WIN32) || defined (_WIN64))
  #define _DIG_LOGGER_API_ 
#else
  #ifdef _DIG_LOGGER_COMPILE_TIME_
    #define _DIG_LOGGER_API_ __declspec(dllexport)
  #else
    #define _DIG_LOGGER_API_ __declspec(dllimport)
  #endif
#endif

#include <string>

namespace DIG {
namespace Logger {

typedef enum { none,error,warning,info,debug,trace } Type;
void _DIG_LOGGER_API_ setFileLogLevel(const char);
void _DIG_LOGGER_API_ setScreenLogLevel(const char);
void _DIG_LOGGER_API_ msg(const char*, const unsigned, const char*, const Type);
void _DIG_LOGGER_API_ msg(const char*, const unsigned, const std::string, const Type);

}}

#ifndef DIG_LOGGER_DISABLE

  #define SETSCREENLOGLEVEL(a) DIG::Logger::setScreenLogLevel(a)
  #define SETFILELOGLEVEL(a) DIG::Logger::setFileLogLevel(a)
  #ifdef DIG_LOGGER_NO_DEBUG
    #define LOG_TRACE(a) 
    #define LOG_DEBUG(a) 
  #else
    #define LOG_TRACE(a) DIG::Logger::msg(__FILE__,__LINE__, a ,DIG::Logger::trace)
    #define LOG_DEBUG(a) DIG::Logger::msg(__FILE__,__LINE__, a ,DIG::Logger::debug)
  #endif
  #define LOG_ERROR(a) DIG::Logger::msg(__FILE__,__LINE__, a ,DIG::Logger::error)
  #define LOG_WARN(a) DIG::Logger::msg(__FILE__,__LINE__, a ,DIG::Logger::warning)
  #define LOG_WARNING(a) DIG::Logger::msg(__FILE__,__LINE__, a ,DIG::Logger::warning)
  #define LOG_INFO(a) DIG::Logger::msg(__FILE__,__LINE__, a ,DIG::Logger::info)

#else

  #define SETSCREENLOGLEVEL(a) 
  #define SETFILELOGLEVEL(a) 
  #define LOG_TRACE(a) 
  #define LOG_DEBUG(a) 
  #define LOG_ERROR(a) 
  #define LOG_WARN(a) 
  #define LOG_WARNING(a) 
  #define LOG_INFO(a) 

#endif

#endif