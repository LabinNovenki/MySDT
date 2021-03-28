# cmake_minimum_required(VERSION <specify CMake version here>)
project(calculator)

set(CMAKE_CXX_STANDARD 14)

add_executable(calculator main.cpp math_.cpp id_table.cpp stack.cpp lexical.cpp parsing.cpp err_deal.cpp err_deal.h)