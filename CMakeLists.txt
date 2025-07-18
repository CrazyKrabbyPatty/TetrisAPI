cmake_minimum_required(VERSION 3.31)
project(TetrisAPI)

set(CMAKE_CXX_STANDARD 17)

find_package(SWIG REQUIRED)
include(UseSWIG)

find_package(Python3 REQUIRED COMPONENTS Development Interpreter)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# 👇 Важно: избежать использования debug-интерфейса Python
add_definitions(-DPy_NO_DEBUG)

set_source_files_properties(TetrisAPI.i PROPERTIES CPLUSPLUS ON)
swig_add_library(TetrisAPI
        LANGUAGE python
        SOURCES TetrisAPI.i TetrisAPI.cpp TetrisAPI.h
)

target_link_libraries(TetrisAPI PRIVATE Python3::Python)

if(WIN32)
    target_compile_definitions(TetrisAPI PRIVATE TetrisAPI_EXPORTS)

    # ❌ Убираем попытку подключения несуществующего python311_d.lib
    # ✅ Вместо этого используем release-библиотеку даже в Debug-сборке
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        message(STATUS "Using Release Python runtime in Debug build")
        # Убедимся, что никакие debug-флаги Python не мешают
        target_compile_definitions(TetrisAPI PRIVATE Py_NO_DEBUG)
    endif()
endif()