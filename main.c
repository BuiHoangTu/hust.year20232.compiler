#include <stdio.h>
#include "lexical_parser.h"

int main(int argc, char const *argv[])
{
    LexicalStream *lexicalStream = createLexicalStream("test.pl0");
    
    Token token;
    do {
        token = nextToken(lexicalStream);
        printf("%d - %d - %s\n", token.type, token.number, token.id);
    } while (token.type != NONE);

    freeLexicalStream(lexicalStream);
}
