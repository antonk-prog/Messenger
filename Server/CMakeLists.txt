cmake_minimum_required(VERSION 3.25)

set(CUR_DIR ${CMAKE_CURRENT_LIST_DIR})

file(GLOB Server_src
    "${CUR_DIR}/*.cpp"
)
add_executable(Server ${Server_src})
include_directories(${CUR_DIR})

message("Server config done")

