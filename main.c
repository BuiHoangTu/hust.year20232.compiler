#include <stdio.h>
#include "lexical_parser.h"

int main(int argc, char const *argv[])
{
    LexicalStream *lexicalStream = createLexicalStream("test.pl0");
    
    Token token;
    do {
        token = nextToken(lexicalStream);
        printf("%-20s | %-20d | %-20s\n", GetTokenType(token), token.number, token.id);
    } while (token.type != NONE);

    freeLexicalStream(lexicalStream);
}
