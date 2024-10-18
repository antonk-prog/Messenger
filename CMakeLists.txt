cmake_minimum_required(VERSION 3.25)
project(Messenger)

set(CMAKE_CXX_STANDARD 20)
set(NLOHMANN_HEADERS "/home/anton/projects/cppLibs/json/nlohmann")
set(HTTP_PARSER_HEADERS "/home/anton/projects/cppLibs/httpparser-master/src")
include_directories(
    ${NLOHMANN_HEADERS}
    ${HTTP_PARSER_HEADERS}
)

add_subdirectory(Client)
add_subdirectory(Server)


set(BIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin")
install(TARGETS Client RUNTIME DESTINATION ${BIN_DIR}) 
install(TARGETS Server RUNTIME DESTINATION ${BIN_DIR}) 