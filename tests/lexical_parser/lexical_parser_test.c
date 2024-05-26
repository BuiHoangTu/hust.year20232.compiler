#include "lexical_parser.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
    if (argc != 3) {
        printf("Argument count mismatch, required 2: pl0 source and expected.txt\n");
    }

    LexicalStream *lexicalStream = createLexicalStream(argv[1]);

    if (lexicalStream->source == NULL) {
        printf("Error opening source file\n");
        exit(1);
    }

    FILE *expected = fopen(argv[2], "r");
    if (expected == NULL) {
        printf("Error opening expected file\n");
        exit(1);
    }

    Token token;
    char tokenStr[100];
    char expectedTokenStr[100];

    int i = 0;
    do
    {
        i++;

        token = nextToken(lexicalStream);
        tokenToString_static(token, tokenStr, 99);

        if (fgets(expectedTokenStr, 99, expected) == NULL) {
            printf("Expected file ended before lexical parser\n");
            printf("At token %d\n", i);
            exit(1);
        }

        if (strncmp(tokenStr, expectedTokenStr, strlen(tokenStr)) != 0) {
            printf("Token mismatch\n");
            printf("Expected: %s\n", expectedTokenStr);
            printf("Got: %s\n", tokenStr);
            printf("At token %d\n", i);
            exit(1);
        }

    } while (token.type != NONE);

    freeLexicalStream(lexicalStream);
}
