cmake_minimum_required (VERSION 2.8.12.2)

project (Vector)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++17 -pthread -g")

set(CMAKE_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Build")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


add_subdirectory(Lib)
add_subdirectory(App)
add_subdirectory(Test)
