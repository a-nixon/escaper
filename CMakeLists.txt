cmake_minimum_required(VERSION 3.26)

project(escaper VERSION 1.0.0)
add_executable(escaper main.cpp)

install(TARGETS escaper DESTINATION bin)
