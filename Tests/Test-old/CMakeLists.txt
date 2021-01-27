ADD_SUBDIRECTORY (googletest)

enable_testing()
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../Source/")

file(GLOB MODELS_TESTS "${CMAKE_CURRENT_SOURCE_DIR}/ContainerTests/*.cpp")
set(TEST_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/Test.cpp"
    "${MODELS_TESTS}"
)

add_executable(Test ${TEST_SRCS})

target_link_libraries(Test gtest gtest_main)
target_link_libraries(Test Lib)

add_test(Test Test)
