#include <stdio.h>
#include <ctype.h>

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

Token nextToken(LexicalStream *lexicalStream)
{
    Token token;
    char c = lexicalStream->lastChar;

    // Skip whitespace
    while (isspace(c))
    {
        c = fgetc(lexicalStream->source);
    }

    // End of file
    if (c == EOF)
    {
        token.type = NONE;
        return token;
    }

    // Check for single-character tokens
    switch (c)
    {
    case '+':
        token.type = PLUS;
        break;
    case '-':
        token.type = MINUS;
        break;
    case '*':
        token.type = TIMES;
        break;
    case '/':
        token.type = SLASH;
        break;
    case '=':
        token.type = EQU;
        break;
    case '<':
        if ((c = fgetc(lexicalStream->source)) == '>')
        {
            token.type = NEQ;
        }
        else if (c == '=')
        {
            token.type = LEQ;
        }
        else
        {
            lexicalStream->lastChar = c;
            token.type = LSS;
        }
        break;
    case '>':
        if ((c = fgetc(lexicalStream->source)) == '=')
        {
            token.type = GEQ;
        }
        else
        {
            lexicalStream->lastChar = c;
            token.type = GTR;
        }
        break;
    case '(':
        token.type = LPARENT;
        break;
    case ')':
        token.type = RPARENT;
        break;
    case '[':
        token.type = LBRACK;
        break;
    case ']':
        token.type = RBRACK;
        break;
    case '.':
        token.type = PERIOD;
        break;
    case ',':
        token.type = COMMA;
        break;
    case ';':
        token.type = SEMICOLON;
        break;
    case '%':
        token.type = PERCENT;
        break;
    default:
        // Check for identifiers or numbers
        if (isdigit(c))
        {
            token.type = NUMBER;
            token.number = c - '0';
            while (isdigit(c = fgetc(lexicalStream->source)))
            {
                token.number = token.number * 10 + (c - '0');
            }
            lexicalStream->lastChar = c;
        }
        else if (isalpha(c))
        {
            token.type = IDENT;
            token.id[0] = c;
            int i = 1;
            while (isalnum(c = fgetc(lexicalStream->source)) && i <= IDENT_MAX_LEN)
            {
                token.id[i++] = c;
            }
            token.id[i] = '\0';
            lexicalStream->lastChar = c;

            // TODO: check other keywords
        }
        else
        {
            // TODO: Handle unrecognized characters
            token.type = NONE;
        }
        break;
    }

    return token;
}

int main(int argc, char const *argv[])
{
    FILE *sourceCode = fopen(argv[2], "r");
    printf("Compiler class");
    return 0;
}
