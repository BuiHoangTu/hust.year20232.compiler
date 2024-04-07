@echo off

rem Compile lexical_parser.c
gcc -c lexical_parser.c -o lexical_parser.o

rem Create lexical_parser library
gcc -shared -o liblexical_parser.a lexical_parser.o

rem Compile and link prog.cpp (or whatever your main program file is)
gcc -c prog.cpp -o prog.o
gcc prog.o -o prog.exe -L. -llexical_parser

rem Clean up intermediate files
del *.o