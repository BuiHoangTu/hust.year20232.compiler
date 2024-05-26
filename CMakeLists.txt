cmake_minimum_required(VERSION 3.22)
project(InYear4_2_Compiler C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(minilib)
include_directories(minilib)

add_executable(prog
        main.c
)

# Include the directory containing other source files
target_include_directories(prog PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# lexical_parser
add_library(lexical_parser lexical_parser.c)
target_link_libraries(prog PRIVATE lexical_parser)

# syntax_analyser
add_library(syntax_analyser syntax_analyser.c)
target_link_libraries(syntax_analyser PRIVATE lexical_parser)
target_link_libraries(prog PRIVATE syntax_analyser)


# test
enable_testing()

## lexical_parser
add_executable(lexical_parser_test tests/lexical_parser/lexical_parser_test.c)
target_include_directories(lexical_parser_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(lexical_parser_test PRIVATE lexical_parser)
### test files
foreach(file_base IN ITEMS test1 test2 test3) # test cases
    foreach(ext IN ITEMS .pl0 .expected.txt) # file extensions
        configure_file(tests/lexical_parser/${file_base}${ext} tests/lexical_parser/${file_base}${ext} COPYONLY)
    endforeach()
endforeach()
### test cases
add_test(NAME lexical_parser_test1 COMMAND lexical_parser_test ${CMAKE_CURRENT_BINARY_DIR}/tests/lexical_parser/test1.pl0 ${CMAKE_CURRENT_BINARY_DIR}/tests/lexical_parser/test1.expected.txt)
add_test(NAME lexical_parser_test2 COMMAND lexical_parser_test ${CMAKE_CURRENT_BINARY_DIR}/tests/lexical_parser/test2.pl0 ${CMAKE_CURRENT_BINARY_DIR}/tests/lexical_parser/test2.expected.txt)
add_test(NAME lexical_parser_test3 COMMAND lexical_parser_test ${CMAKE_CURRENT_BINARY_DIR}/tests/lexical_parser/test3.pl0 ${CMAKE_CURRENT_BINARY_DIR}/tests/lexical_parser/test3.expected.txt)

## syntax_analyser
add_executable(syntax_analyser_test tests/syntax_analyser/syntax_analyser_test.c)
target_include_directories(syntax_analyser_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(syntax_analyser_test PRIVATE syntax_analyser)
### test files
# configure_file(tests/syntax_analyser/test1.pl0 tests/syntax_analyser/test1.pl0 COPYONLY)