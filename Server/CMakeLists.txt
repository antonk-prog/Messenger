cmake_minimum_required(VERSION 3.25)

set(CUR_DIR ${CMAKE_CURRENT_LIST_DIR})


add_subdirectory(API)
add_subdirectory(Collector)

add_executable(Server ServerApp.cpp)


target_include_directories(ServerAPI PUBLIC Collector)
target_include_directories(Server PUBLIC API)

find_package(OpenSSL REQUIRED)

target_link_libraries(Server ServerAPI)
target_link_libraries(Server Collector)
target_link_libraries(Server OpenSSL::Crypto)

