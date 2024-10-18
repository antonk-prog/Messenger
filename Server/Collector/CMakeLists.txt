cmake_minimum_required(VERSION 3.25)
set(CUR_DIR ${CMAKE_CURRENT_LIST_DIR})
file(GLOB Collector
    "${CUR_DIR}/*.cpp"
)

include_directories(${CUR_DIR})

add_library( Collector ${Collector})
