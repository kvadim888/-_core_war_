cmake_minimum_required(VERSION 3.7.2)
project(libft C)

set(CMAKE_C_STANDARD 99)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/sources/ft_memory MEMORY)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/sources/ft_printf/src PRINTF)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/sources/ft_string STRING)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/sources/ft_list LIST)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/sources/ft_sys SYS)

add_library(ft STATIC ${MEMORY} ${STRING} ${PRINTF} ${LIST} ${SYS})

add_custom_command(TARGET ft POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan
        "Libft building complete")

target_include_directories(ft PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)

add_executable(test main.c)
target_include_directories(test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)
target_link_libraries(test ft)
