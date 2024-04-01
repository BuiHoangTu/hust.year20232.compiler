#include <stdio.h>

#define IDENT_MAX_LEN 20

typedef enum
{
    NONE = 0,
    IDENT,
    NUMBER,
    BEGIN,
    CALL,
    CONST,
    DO,
    ELSE,
    END,
    FOR,
    IF,
    ODD,
    PROCEDURE,
    PROGRAM,
    THEN,
    TO,
    VAR,
    WHILE,
    PLUS,
    MINUS,
    TIMES,
    SLASH,
    EQU,
    NEQ,
    LSS,
    LEQ,
    GTR,
    GEQ,
    LPARENT,
    RPARENT,
    LBRACK,
    RBRACK,
    PERIOD,
    COMMA,
    SEMICOLON,
    ASSIGN,
    PERCENT

} TokenType;

typedef struct token
{
    TokenType type;
    int number;
    char id[IDENT_MAX_LEN + 1];
} Token;

typedef struct lexical_stream
{
    FILE *source;
    char lastChar;
} LexicalStream;


Token nextToken(LexicalStream lexicalStream) {
    char ch = lexicalStream.lastChar;

    do {

    } while(ch = fgetc(lexicalStream.source));

    
}

int main(int argc, char const *argv[])
{
    FILE *sourceCode = fopen(argv[2], "r");
    printf("Compiler class");
    return 0;
}
