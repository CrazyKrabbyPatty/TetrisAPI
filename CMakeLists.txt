cmake_minimum_required(VERSION 3.31)
project(TetrisAPI)

set(CMAKE_CXX_STANDARD 17)

find_package(SWIG REQUIRED)
include(UseSWIG)

find_package(Python3 REQUIRED COMPONENTS Development Interpreter)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_definitions(-DPy_NO_DEBUG)

set_source_files_properties(TetrisAPI.i PROPERTIES CPLUSPLUS ON)
swig_add_library(TetrisAPI
        LANGUAGE python
        SOURCES TetrisAPI.i TetrisAPI.cpp TetrisAPI.h
)

target_link_libraries(TetrisAPI PRIVATE Python3::Python)

if(WIN32)
    set(MODULE_EXTENSION "pyd")
    target_compile_definitions(TetrisAPI PRIVATE TetrisAPI_EXPORTS)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        message(STATUS "Using Release Python runtime in Debug build")
        target_compile_definitions(TetrisAPI PRIVATE Py_NO_DEBUG)
    endif()
    set_target_properties(TetrisAPI PROPERTIES
            SUFFIX ".${MODULE_EXTENSION}"
            PREFIX ""
    )
else()
    set(MODULE_EXTENSION "so")
    target_compile_definitions(TetrisAPI PRIVATE TetrisAPI_EXPORTS)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        message(STATUS "Using Release Python runtime in Debug build")
        target_compile_definitions(TetrisAPI PRIVATE Py_NO_DEBUG)
    endif()
    set_target_properties(TetrisAPI PROPERTIES
            LINK_FLAGS "-undefined dynamic_lookup"
            SUFFIX ".${MODULE_EXTENSION}"
            PREFIX ""
    )
endif()

message(STATUS "Python include dirs: ${Python3_INCLUDE_DIRS}")
message(STATUS "Python libraries: ${Python3_LIBRARIES}")
message(STATUS "Building for ${CMAKE_SYSTEM_NAME}, module extension: ${MODULE_EXTENSION}")