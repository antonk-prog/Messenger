cmake_minimum_required(VERSION 3.25)
set(CUR_DIR ${CMAKE_CURRENT_LIST_DIR})
file(GLOB Server_api
    "${CUR_DIR}/*.cpp"
)
add_library( ServerAPI ${Server_api})

include_directories(
    ${CUR_DIR}    
)


