cmake_minimum_required(VERSION 3.25)

add_subdirectory(API)

add_executable(Server ServerApp.cpp)


target_include_directories(Server PUBLIC API)

target_link_libraries(Server PUBLIC ServerAPI)
