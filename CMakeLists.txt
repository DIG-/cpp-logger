cmake_minimum_required(VERSION 3.1)
project(DIG-Logger VERSION 1.0.0 LANGUAGES CXX)

list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_library(dig-logger STATIC)
target_include_directories(dig-logger PUBLIC include)
target_sources(dig-logger PRIVATE src/logger.cpp)
target_compile_definitions(dig-logger PUBLIC DIG_LOGGER_STATIC)

include(InstallTargets)
install_targets(TARGETS dig-logger NAMESPACE dig-logger)
