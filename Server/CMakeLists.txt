cmake_minimum_required(VERSION 3.25)

set(CUR_DIR ${CMAKE_CURRENT_LIST_DIR})
set(NLOHMANN_HEADERS "/home/anton/projects/cppLibs/json/nlohmann")
set(HTTP_PARSER_HEADERS "/home/anton/projects/cppLibs/httpparser-master/src")

add_subdirectory(API)
add_subdirectory(Collector)

add_executable(Server ServerApp.cpp)


target_include_directories(ServerAPI PUBLIC Collector)
target_include_directories(ServerAPI PUBLIC ${HTTP_PARSER_HEADERS})
target_include_directories(Server PUBLIC API)
target_include_directories(Server PUBLIC ${NLOHMANN_HEADERS})

find_package(OpenSSL REQUIRED)

target_link_libraries(Server ServerAPI)
target_link_libraries(Server Collector)
target_link_libraries(Server OpenSSL::Crypto)

