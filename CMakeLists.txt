cmake_minimum_required (VERSION 2.8.12.2)

project (SharpVector)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++17 -g -Wno-unknown-pragmas")

set(CMAKE_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Build/Source")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


add_subdirectory(Source)
