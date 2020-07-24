set(LIB_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/Wrapper/Container.cpp"
    "Vector.cpp"
)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

add_library(Lib STATIC ${LIB_SRCS})
