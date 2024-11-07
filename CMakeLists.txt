cmake_minimum_required(VERSION 3.25)
set(CMAKE_CPP_COMPILER ${C_COMPILER})
project(Messenger)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CUR_DIR ${CMAKE_CURRENT_LIST_DIR})
set(HTTP_PARSER_HEADERS "${CUR_DIR}/deps/httpparser/src")
set(HTTP_REQUEST_HEADERS "${CUR_DIR}/deps/httprequest")
set(NLOHMANN_HEADERS "${CUR_DIR}/deps/nlohmann/include")
set(LIBPQXX_HEADERS "${CUR_DIR}/deps/libpqxx")
set(SQLBUILDER_HEADERS "${CUR_DIR}/deps/sqlbuilder")
set(BIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin")
add_subdirectory(Client)
add_subdirectory(Server)

find_package(OpenSSL REQUIRED)

target_include_directories(ServerAPI PUBLIC ${NLOHMANN_HEADERS})
target_include_directories(ServerAPI PUBLIC ${HTTP_PARSER_HEADERS})
target_include_directories(ServerAPI PUBLIC ${SQLBUILDER_HEADERS})
target_include_directories(Server PUBLIC ${NLOHMANN_HEADERS})
target_include_directories(Server PUBLIC ${LIBPQXX_HEADERS})
add_subdirectory(${LIBPQXX_HEADERS})
target_link_libraries(ServerAPI PUBLIC pqxx)

target_link_libraries(Server PUBLIC OpenSSL::Crypto)



install(TARGETS Client RUNTIME DESTINATION ${BIN_DIR})
install(TARGETS Server RUNTIME DESTINATION ${BIN_DIR})