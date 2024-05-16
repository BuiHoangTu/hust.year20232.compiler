cmake_minimum_required(VERSION 3.22)
project(InYear4_2_Compiler C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(minilib)
include_directories(minilib)

add_executable(prog
        main.c
        lexical_parser.c
        lexical_parser.h
)








# Add the target for lexical_parser.c
add_library(lexical_parser lexical_parser.c)

## Add the target for lexical_parser.c
#add_library(lexical_parser lexical_parser.c)
#
## Include the directory containing lexical_parser.h
#target_include_directories(prog PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#
## Link the main executable with the lexical parser library
#target_link_libraries(prog PRIVATE lexical_parser)

configure_file(test.pl0 test.pl0 COPYONLY)
