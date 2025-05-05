cmake_minimum_required(VERSION 3.22.1)

project("kakuluwa")

add_library(${CMAKE_PROJECT_NAME} SHARED
        native-lib.cpp
        xxtea.cpp)  # <-- add this line

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR})  # <-- add this line

target_link_libraries(${CMAKE_PROJECT_NAME}
        android
        log)