#include <dig-logger/logger.hpp>
#include <dig-logger/util/filter.hpp>
#include <dig-logger/util/union.hpp>
#include <dig-logger/printer/stdout.hpp>
#include <iostream>


int main(int argc, char** argv) {
  std::unique_ptr<DIG::Logger::LoggerInterface> printer = std::make_unique<DIG::Logger::Printer::StdOut>();
  DIG::Logger::Logger logger(printer,"demo");
  logger.v("verbose test");
  logger.d("debug test");
  logger.i("info test");
  logger.w("warning test");
  logger.e("error test");
  logger.assert("assert test");
  return 0;
}