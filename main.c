#include <stdio.h>
#include "lexical_parser.h"

int main(int argc, char const *argv[])
{
    LexicalStream *lexicalStream = createLexicalStream("test.pl0");

    Token token;
    char tokenStr[100];
    do
    {
        token = nextToken(lexicalStream);
        tokenToString_static(token, tokenStr, 99);
        printf("%s\n", tokenStr);
    } while (token.type != NONE);

    freeLexicalStream(lexicalStream);
}
