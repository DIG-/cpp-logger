#include <dig-logger/util/filter.hpp>
#include <stdexcept>

using namespace DIG::Logger;

int main(int argc, char** argv) {
  try {
    Util::Filter test1(std::unique_ptr<LoggerInterface>(nullptr), Level::NONE);
  } catch (std::runtime_error& error) {
    return 0;
  }
  return -1;
}