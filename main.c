#include <stdio.h>
#include "lexical_parser.h"

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        printf("Số lượng tham số không đúng. Yêu cầu: 1. Hiện có %d.\n", argc - 1);
    }

    LexicalStream *lexicalStream = createLexicalStream(argv[1]);

    if (lexicalStream->source == NULL) {
        printf("Lỗi mở file %s", argv[1]);
    }

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
