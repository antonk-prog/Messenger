cmake_minimum_required(VERSION 3.25)

set(CUR_DIR ${CMAKE_CURRENT_LIST_DIR})

add_executable(Client ClientApp.cpp)
target_link_libraries(Client PRIVATE ncurses)