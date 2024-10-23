cmake_minimum_required(VERSION 3.25)

set(CUR_DIR ${CMAKE_CURRENT_LIST_DIR})

FILE(GLOB Client_gui
    "${CUR_DIR}/*.cpp")

include_directories(
    ${CUR_DIR}    
)
    
add_library(Client_gui ${Client_gui})
