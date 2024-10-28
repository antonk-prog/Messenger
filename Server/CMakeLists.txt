cmake_minimum_required(VERSION 3.25)

set(CUR_DIR ${CMAKE_CURRENT_LIST_DIR})
set(NLOHMANN_HEADERS "/home/vova/projects/cppLibs/json/include/")
set(HTTP_PARSER_HEADERS "/home/vova/projects/cppLibs/httpparser-master/src")
find_package(OpenSSL REQUIRED)

add_subdirectory(API)
add_subdirectory(Collector)
add_subdirectory(deps/libpqxx)
add_executable(Server ServerApp.cpp)


target_include_directories(ServerAPI PUBLIC Collector)
target_include_directories(ServerAPI PUBLIC ${HTTP_PARSER_HEADERS})
target_include_directories(ServerAPI PUBLIC ${NLOHMANN_HEADERS})

target_include_directories(Server PUBLIC API)
target_include_directories(Server PUBLIC ${NLOHMANN_HEADERS})


target_link_libraries(Collector PUBLIC pqxx)
target_link_libraries(Server PUBLIC Collector)
target_link_libraries(ServerAPI PUBLIC pqxx)
target_link_libraries(Server PUBLIC ServerAPI)
target_link_libraries(Server PUBLIC OpenSSL::Crypto)

