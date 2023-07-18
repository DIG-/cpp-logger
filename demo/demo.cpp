#include <dig-logger/creator.hpp>
#include <dig-logger/logger.hpp>
#include <dig-logger/printer/html.hpp>
#include <dig-logger/printer/plain.hpp>
#include <dig-logger/printer/stdout.hpp>
#include <dig-logger/util/filter.hpp>
#include <dig-logger/util/union.hpp>
#include <iostream>

int main(int argc, char** argv) {
  auto p_stdout = std::make_unique<DIG::Logger::Printer::StdOut>();
  auto p_plain = std::make_unique<DIG::Logger::Printer::Plain>("demo.txt");
  auto p_html = std::make_unique<DIG::Logger::Printer::Html>("demo.htm");

  DIG::Logger::Logger logger =
      DIG::Logger::create(std::make_shared<DIG::Logger::Util::Union<3>>(p_stdout, p_plain, p_html), "demo");

  logger.v("verbose test");
  logger.d("debug test");
  logger.i("info test");
  logger.w("warning test");
  logger.e("error test");
  logger.assert("assert test");
  return 0;
}