#include <dig-logger/logger.hpp>
#include <dig-logger/util/filter.hpp>
#include <dig-logger/util/union.hpp>
#include <iostream>

int main(int argc, char** argv) {
  DIG::Logger::Util::Filter filter(nullptr, DIG::Logger::Level::VERBOSE);
  DIG::Logger::Util::Union<2> joint({nullptr, nullptr});
  filter.log(DIG::Logger::Level::VERBOSE, "a", std::optional<std::exception>(), "", std::source_location::current());
  std::cout << "Run" << std::endl;
  return 0;
}