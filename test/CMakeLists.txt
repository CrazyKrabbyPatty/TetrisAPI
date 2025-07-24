add_executable(test_tetris test_tetris.cpp)

# Добавляем директорию, где лежит TetrisAPI.h
target_include_directories(test_tetris PRIVATE ${CMAKE_SOURCE_DIR})

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

# Линкуем с основной библиотекой
target_link_libraries(test_tetris PRIVATE TetrisAPI gtest gtest_main)

# Подключаем тесты
add_test(NAME TetrisTests COMMAND test_tetris)
