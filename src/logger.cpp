#include "logger.hpp"

#if defined(_MSC_VER) || defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#define _DIG_LOGGER_WINDOWS_ 1
#endif

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#ifndef DIG_LOGGER_SCREEN_NO_THREAD
#include <thread>
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

void fill_time_info(std::ostream& output,
                    const std::chrono::milliseconds& time) {
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
  fill_time_info(SS, time);
  return SS.str();

  // return std::put_time(std::ctime(),)
}

inline char type_as_char(const Type type) {
  switch (type) {
    case Type::error:
      return 'E';
    case Type::warning:
      return 'W';
    case Type::info:
      return 'I';
    case Type::debug:
      return 'D';
  }
  return 'V';
}

#ifdef _DIG_LOGGER_WINDOWS_
inline uint_fast8_t get_windows_terminal_color(const Type type) {
  switch (type) {
    case Type::error:
      return 12;
    case Type::warning:
      return 14;
    case Type::info:
      return 11;
    case Type::debug:
      return 7;
  }
  return 8;
}
#else
inline const std::string get_other_terminal_color(const Type type) {
  switch (type) {
    case Type::error:
      return "\x1b[31m";
    case Type::warning:
      return "\x1b[1;33m";
    case Type::info:
      return "\x1b[0;36m";
    case Type::debug:
      return "\x1b[1;37m";
  }
  return "\x1B[0m";
}
#endif

inline void apply_terminal_color(std::ostream& output, const Type type) {
#ifdef _DIG_LOGGER_WINDOWS_
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, get_windows_terminal_color(type));
#else
  output << get_other_terminal_color(type);
#endif
}

inline void clear_terminal_color(std::ostream& output) {
#ifdef _DIG_LOGGER_WINDOWS_
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, 7);
#else
  output << "\x1B[0m";
#endif
}

inline void fill_thread_info(std::ostream& output) {
#ifndef DIG_LOGGER_SCREEN_NO_THREAD
  output << " #" << std::setfill('0') << std::setw(2)
         << std::this_thread::get_id();
#endif
}

inline void fill_file_info(std::ostream& output,
                           const char* filename,
                           const unsigned line) {
#ifndef DIG_LOGGER_SCREEN_NO_FILE
  output << " " << filename << " @" << std::setfill('0') << std::setw(4)
         << line;
#endif
}

void msg(const char* filename,
         const unsigned line,
         const std::string message,
         const Type type) {
  auto diffTime = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now() - start);
  mtx.lock();
  if (type <= screen_type) {
    apply_terminal_color(std::cout, type);
    fill_time_info(std::cout, diffTime);
    std::cout << " [" << type_as_char(type) << "]";
    fill_thread_info(std::cout);
    fill_file_info(std::cout, filename, line);
    std::cout << ": " << message << "\n";
    clear_terminal_color(std::cout);
  }
  if ((type <= file_type) && (file.good())) {
    file << "<tr class='level_" << (int)type << "'><td class='time'>"
         << formatTime(diffTime) << "</td><td class='line'>"
         << std::this_thread::get_id() << "</td><td class='line'>" << line
         << "</td><td class='file'>" << filename << "</td><td class='message'>"
         << message << "</td></tr>\n";
  }
  mtx.unlock();
}

}  // namespace Logger
}  // namespace DIG