#include <stdio.h>
#include <stdlib.h>
#include "lexical_parser.h"

int main(int argc, char const *argv[])
{
    FILE *sourceCode = fopen("test.pl0", "r");
    
    LexicalStream *lexicalStream = malloc(sizeof(LexicalStream));
    lexicalStream->lastChar = ' ';
    lexicalStream->source = sourceCode;
    
    Token token;
    do {
        token = nextToken(lexicalStream);
        printf("%d - %d - %s\n", token.type, token.number, token.id);
    } while (token.type != NONE);

    fclose(sourceCode);
}
