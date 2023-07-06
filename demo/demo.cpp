#include <dig-logger/logger.hpp>
#include <dig-logger/printer/html.hpp>
#include <dig-logger/printer/plain.hpp>
#include <dig-logger/printer/stdout.hpp>
#include <dig-logger/util/filter.hpp>
#include <dig-logger/util/union.hpp>
#include <iostream>

int main(int argc, char** argv) {
  std::unique_ptr<DIG::Logger::LoggerInterface> p_stdout = std::make_unique<DIG::Logger::Printer::StdOut>();
  std::unique_ptr<DIG::Logger::LoggerInterface> p_plain = std::make_unique<DIG::Logger::Printer::Plain>("demo.txt");
  std::unique_ptr<DIG::Logger::LoggerInterface> p_html = std::make_unique<DIG::Logger::Printer::Html>("demo.htm");
  std::array<std::unique_ptr<DIG::Logger::LoggerInterface>, 3> printers = {std::move(p_stdout), std::move(p_plain),
                                                                           std::move(p_html)};
  // auto printer = std::make_shared<DIG::Logger::Util::Union<3>>(printers);
  DIG::Logger::Logger logger(std::make_shared<DIG::Logger::Util::Union<3>>(printers), "demo");
  logger.v("verbose test");
  logger.d("debug test");
  logger.i("info test");
  logger.w("warning test");
  logger.e("error test");
  logger.assert("assert test");
  return 0;
}