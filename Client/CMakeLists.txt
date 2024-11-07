cmake_minimum_required(VERSION 3.25)

set(CUR_DIR ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(Client_gui)
add_subdirectory(Client_network)

add_executable(Client client.cpp)

target_include_directories(Client PUBLIC Client_gui)
target_link_libraries(Client PRIVATE Client_gui)
target_link_libraries(Client PRIVATE Client_network)
target_link_libraries(Client PRIVATE ncursesw)
target_link_libraries(Client PRIVATE menuw)
