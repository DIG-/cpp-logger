#include <dig-logger/creator.hpp>
#include <dig-logger/printer/stub.hpp>
#include <stdexcept>

using namespace DIG::Logger;

int main(int argc, char** argv) {
  try {
    auto logger = Logger(std::make_shared<std::string>(""), "test");
  } catch (std::logic_error& error) {
    auto logger = Logger(std::make_shared<Printer::Stub>(), "test");
    return 0;
  }
  return -1;
}