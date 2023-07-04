#pragma once

#include <dig-logger/interface.hpp>
#include <dig-logger/printer/stream.hpp>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <ostream>

namespace DIG {
namespace Logger {
namespace Printer {

class Plain : public Stream {
 public:
  Plain(std::ostream& output) : Stream(output) { header(); }
  Plain(std::ofstream&& file) : file(std::move(file)), Stream(file) { header(); }
  Plain(const std::string_view filename) : file(filename.data(), std::fstream::trunc), Stream(file) { header(); }
  Plain(std::filesystem::path& filename) : file(filename.c_str(), std::fstream::trunc), Stream(file) { header(); }
  ~Plain() { footer(); }

  void log(                                            //
      const Level level,                               //
      const std::string_view tag,                      //
      const std::optional<std::exception>& exception,  //
      const std::string_view message,                  //
      const std::source_location& source               //
  );

 private:
  void header();
  void footer();

  std::ofstream file;
  std::mutex mutex;
};

}  // namespace Printer
}  // namespace Logger
}  // namespace DIG