cmake_minimum_required(VERSION 3.16)
project(TetrisAPI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указание путей к Python
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

# Создание библиотеки TetrisAPI только один раз
add_library(TetrisAPI STATIC TetrisAPI.cpp TetrisAPI.h)

# Подключаем заголовки Python
target_include_directories(TetrisAPI PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(TetrisAPI PRIVATE Python3::Python)

# Подключаем GoogleTest
add_subdirectory(googletest)
enable_testing()
add_subdirectory(test)
