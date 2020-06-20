set(APP_SRCS 
    "${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp"
)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../Lib/")

add_executable(App ${APP_SRCS} ${INCLUDES})
target_link_libraries(App Lib)
