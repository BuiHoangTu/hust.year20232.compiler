#include "syntax_analyser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <input_file>\n", argv[0]);
        exit(1);
    }

    LexicalStream *stream = createLexicalStream(argv[1]);

    if (argc == 3)
    {
        if (strcmp(argv[2], "-f") == 0)
        {
            factor(stream);
        }
        else if (strcmp(argv[2], "-t") == 0)
        {
            term(stream);
        }
        else if (strcmp(argv[2], "-e") == 0)
        {
            expression(stream);
        }
        else if (strcmp(argv[2], "-c") == 0)
        {
            condition(stream);
        }
        else if (strcmp(argv[2], "-s") == 0)
        {
            statement(stream);
        }
        else if (strcmp(argv[2], "-b") == 0)
        {
            block(stream);
        }
        else if (strcmp(argv[2], "-p") == 0)
        {
            program(stream);
        }
        else
        {
            printf("Invalid flag\n");
            exit(1);
        }
    }
    else
    {
        program(stream);
    }

    if (nextToken(stream).type == NONE)
    {
        printf("Syntax is correct\n");
    return 0;
    }
    else
    {
        char tokenStr[100];
        tokenToString_static(nextToken(stream), tokenStr, 99);
        printf("There are still tokens. Next is %s\n", tokenStr);
        exit(1);
    }

}