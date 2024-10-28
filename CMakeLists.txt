cmake_minimum_required(VERSION 3.25)
project(Messenger)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_subdirectory(Client)
add_subdirectory(Server)

set(BIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin")
install(TARGETS Client RUNTIME DESTINATION ${BIN_DIR}) 
install(TARGETS Server RUNTIME DESTINATION ${BIN_DIR}) 