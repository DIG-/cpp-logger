#include <iostream>
#include <dig-logger/logger.hpp>
#include <dig-logger/util/filter.hpp>

int main(unsigned argc, char**argv){
    DIG::Logger::Util::Filter filter(nullptr, DIG::Logger::Level::VERBOSE);
    filter.log(DIG::Logger::Level::VERBOSE,"a",std::optional<std::exception>(),"",std::source_location::current());
    std::cout << "Run" << std::endl;
    return 0;
}