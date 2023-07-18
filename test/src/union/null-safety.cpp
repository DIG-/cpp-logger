#include <dig-logger/printer/stdout.hpp>
#include <dig-logger/util/union.hpp>
#include <stdexcept>

using namespace DIG::Logger;

int main(int argc, char** argv) {
  try {
    Util::Union<2> test1(std::unique_ptr<LoggerInterface>(nullptr), std::unique_ptr<LoggerInterface>(nullptr));
  } catch (std::logic_error& error) {
    try {
      Util::Union<2> test2(std::unique_ptr<Printer::StdOut>(), std::unique_ptr<LoggerInterface>(nullptr));
    } catch (std::logic_error& error) {
      try {
        Util::Union<2> test3(std::unique_ptr<LoggerInterface>(nullptr), std::unique_ptr<Printer::StdOut>());
      } catch (std::logic_error& error) {
        return 0;
      }
    }
  }
  return -1;
}