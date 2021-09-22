#include "logger.hpp"

#if defined(_MSC_VER) || defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>

#ifdef DIG_LOGGER_SCREEN_NO_FILE
#define DIG_LOGGER_FILE
#else
#define DIG_LOGGER_FILE \
  << filename << " " << std::setfill('0') << std::setw(4) << line << ":"
#endif
#ifdef DIG_LOGGER_SCREEN_NO_THREAD
#define DIG_LOGGER_THREAD
#else
#define DIG_LOGGER_THREAD << std::this_thread::get_id() << ":"
#endif

namespace DIG {
namespace Logger {

auto start = std::chrono::system_clock::now();
Type screen_type = Type::info;
Type file_type = Type::none;
std::mutex mtx;

std::ofstream file;

void setFileLogLevel(const Type type) {
  file_type = type;
  if (type == none) {
    file.close();
  } else {
    file.open("log.htm");
    if (file.good()) {
      file << "<!DOCTYPE html><head><title>Log</title><style>body { "
              "background:#000; color:ccc; font-family:Verdana; "
              "font-size:12px; }table { width: 100%; border:1px dashed #666; "
              "background:#444; cellpadding:0; cellspacing:0; }tr:hover "
              "{background:#555;}td {padding:1px; color:#aaa; border-right:1px "
              "solid #666; border-bottom:1px solid #666;}th "
              "{color:#666;border-bottom:1px solid #666;}.level_"
           << error
           << " .message:before {content:\"Error: \";color:#f00;}.level_"
           << error << " td {color:#f00;}.level_" << warning
           << " .message:before {content:\"Warning: \";color:#fa0;}.level_"
           << warning << " td {color:#fa0;}.level_" << debug
           << " .message:before {content:\"Debug: \";color:#aaa;}.level_"
           << debug << " td {color:#aaa;}.level_" << trace
           << " .message:before {content:\"Trace: \";color:#666;}.level_"
           << trace << " td {color:#666;}.level_" << info
           << " .message:before {content:\"Information: \";color:#66f;}.level_"
           << info
           << " td {color:#66f;}.time {width:130px;text-align:right;}.file "
              "{width:200px;}.line {text-align:right;width:50px;}th "
              "{text-align:center;}.message {}</style><body><table "
              "cellpadding=0 cellspacing=0><tr><th class='time'>time</th><th "
              "class='line'>thread</th><th class='line'>line</th><th "
              "class='file'>File</th><th class='message'>Message</th></tr>";
      // clang-format off
      /* unoptmized
      Q(output)<<"<!DOCTYPE html><head><title>Log</title><style>";
      Q(output)<<"body { background:#000; color:ccc; font-family:Verdana; font-size:12px; }";
      Q(output)<<"table { width: 100%; border:1px dashed #666; background:#444; cellpadding:0; cellspacing:0; }";
      Q(output)<<"tr:hover {background:#555;}";
      Q(output)<<"td {padding:1px; color:#aaa; border-right:1px solid #666; border-bottom:1px solid #666;}";
      Q(output)<<"th {color:#666;border-bottom:1px solid #666;}";
      Q(output)<<".level_"<<error   <<" .message:before {content:\"Error: \";color:#f00;}";
      Q(output)<<".level_"<<error   <<" td {color:#f00;}";
      Q(output)<<".level_"<<warning <<" .message:before {content:\"Warning: \";color:#fa0;}";
      Q(output)<<".level_"<<warning <<" td {color:#fa0;}";
      Q(output)<<".level_"<<debug   <<" .message:before {content:\"Debug: \";color:#aaa;}";
      Q(output)<<".level_"<<debug   <<" td {color:#aaa;}";
      Q(output)<<".level_"<<trace   <<" .message:before {content:\"Trace: \";color:#666;}";
      Q(output)<<".level_"<<trace   <<" td {color:#666;}";
      Q(output)<<".level_"<<info    <<" .message:before {content:\"Information: \";color:#66f;}";
      Q(output)<<".level_"<<info    <<" td {color:#66f;}";
      Q(output)<<".time {width:130px;text-align:right;}";
      Q(output)<<".file {width:200px;}";
      Q(output)<<".line {text-align:right;width:50px;}";
      Q(output)<<"th {text-align:center;}.message {}";
      Q(output)<<"</style><body><table cellpadding=0 cellspacing=0><tr><th class='time'>time</th><th class='line'>line</th><th class='file'>File</th><th class='message'>Message</th></tr>";
      */
      // clang-format on
    }
  }
}

void setScreenLogLevel(const Type type) {
  screen_type = type;
}

void formatTime(std::ostream& output, const std::chrono::milliseconds& time) {
  unsigned hour = time.count() / (1000 * 60 * 60);
  unsigned hour_rest = time.count() % (1000 * 60 * 60);
  unsigned minute = hour_rest / (1000 * 60);
  unsigned minute_rest = hour_rest % (1000 * 60);
  unsigned second = minute_rest / 1000;
  unsigned millisecond = minute_rest % 1000;
  output << std::setfill('0') << std::setw(2) << hour;
  output << ":" << std::setfill('0') << std::setw(2) << minute;
  output << ":" << std::setfill('0') << std::setw(2) << second;
  output << "." << std::setfill('0') << std::setw(3) << millisecond;
}

inline std::string formatTime(const std::chrono::milliseconds time) {
  std::stringstream SS;
  formatTime(SS, time);
  return SS.str();

  // return std::put_time(std::ctime(),)
}

void msg(const char* filename,
         const unsigned line,
         const std::string message,
         const Type type) {
  std::chrono::milliseconds diffTime =
      std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::system_clock::now() - start);
  mtx.lock();
  if (type <= screen_type) {
#define P                                                              \
  std::cout << "[" << formatTime(diffTime)                             \
            << "]" DIG_LOGGER_THREAD DIG_LOGGER_FILE << " " << message \
            << std::endl;
#if defined(_MSC_VER) || defined(_WIN32) || defined(_WIN64)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(
        hConsole, (type == Logger::error)
                      ? 12
                      : ((type == Logger::warning)
                             ? 14
                             : ((type == Logger::info)
                                    ? 11
                                    : (type == Logger::debug ? 7 : 8))));
    P;
    SetConsoleTextAttribute(hConsole, 7);
#else
    if (type == error)
      std::cout << "\x1b[31m";
    else if (type == warning)
      std::cout << "\x1b[1;33m";
    else if (type == info)
      std::cout << "\x1b[0;36m";
    else if (type == debug)
      std::cout << "\x1B[1;37m";
    P;
    std::cout << "\x1B[0m";
#endif
  }
  if ((type <= file_type) && (file.good())) {
    file << "<tr class='level_" << (int)type << "'><td class='time'>"
         << formatTime(diffTime) << "</td><td class='line'>"
         << std::this_thread::get_id() << "</td><td class='line'>" << line
         << "</td><td class='file'>" << filename << "</td><td class='message'>"
         << message << "</td></tr>" << std::endl;
  }
  mtx.unlock();
}

}  // namespace Logger
}  // namespace DIG