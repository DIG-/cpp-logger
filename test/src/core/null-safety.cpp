#include <dig-logger/creator.hpp>
#include <stdexcept>

using namespace DIG::Logger;

int main(int argc, char** argv) {
  try {
    auto logger = create(std::shared_ptr<LoggerInterface>(nullptr), "test");
  } catch (std::logic_error& error) {
    return 0;
  }
  return -1;
}