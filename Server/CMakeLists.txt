cmake_minimum_required(VERSION 3.25)

add_subdirectory(API)
add_subdirectory(Collector)

add_executable(Server ServerApp.cpp)

target_include_directories(ServerAPI PUBLIC Collector)

target_include_directories(Server PUBLIC API)
target_include_directories(Server PUBLIC Collector)

target_link_libraries(Server PUBLIC Collector)
target_link_libraries(Server PUBLIC ServerAPI)
