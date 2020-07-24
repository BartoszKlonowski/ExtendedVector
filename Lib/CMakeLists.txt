set(LIB_SRCS
    "Vector.cpp"
)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

add_library(Lib STATIC ${LIB_SRCS})
