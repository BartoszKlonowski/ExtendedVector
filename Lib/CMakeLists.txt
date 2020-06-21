set(LIB_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/Vector/Container.cpp"
)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

add_library(Lib STATIC ${LIB_SRCS})
