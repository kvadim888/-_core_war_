cmake_minimum_required(VERSION 3.14)
project(vm C)

set(CMAKE_C_STANDARD 99)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} VM_SRC)

#set(CMAKE_C_FLAGS "-Wall -Wextra -Werror")

add_executable(vm ${VM_SRC} sort_champs.c)

target_include_directories(vm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc
        ${CMAKE_CURRENT_SOURCE_DIR}/../includes
        ${CMAKE_CURRENT_SOURCE_DIR}/../libft/includes)

message("includes = " ${CMAKE_CURRENT_SOURCE_DIR}/../includes "\n"
        ${CMAKE_CURRENT_SOURCE_DIR}/../libft/includes)
message("currentdir = " ${CMAKE_CURRENT_SOURCE_DIR})

target_link_directories(vm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../libft)

target_link_libraries(vm ft)
