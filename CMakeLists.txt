cmake_minimum_required(VERSION 3.24)
project(Args VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(src)

add_executable(guess-number-game main.cpp)
target_link_libraries(guess-number-game PRIVATE guess-number)

add_subdirectory(test)
