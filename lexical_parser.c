#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

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

LexicalStream *createLexicalStream(char *filePath)
{
    LexicalStream *out = malloc(sizeof(LexicalStream));

    out->lastChar = ' ';
    out->source = fopen(filePath, "r");

    return out;
}

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

            //// check other keywords
            if (strcmp("begin", token.id) == 0)
            {
                token.type = BEGIN;
            }
            else if (strcmp("end", token.id) == 0)
            {
                token.type = END;
            }
            else if (strcmp("if", token.id) == 0)
            {
                token.type = IF;
            }
            else if (strcmp("then", token.id) == 0)
            {
                token.type = END;
            }
            else if (strcmp("while", token.id) == 0)
            {
                token.type = WHILE;
            }
            else if (strcmp("do", token.id) == 0)
            {
                token.type = DO;
            }
            else if (strcmp("call", token.id) == 0)
            {
                token.type = CALL;
            }
            else if (strcmp("odd", token.id) == 0)
            {
                token.type = ODD;
            }
            else if (strcmp("to", token.id) == 0)
            {
                token.type = TO;
            }
            else if (strcmp("const", token.id) == 0)
            {
                token.type = CONST;
            }
            else if (strcmp("var", token.id) == 0)
            {
                token.type = VAR;
            }
            else if (strcmp("procedure", token.id) == 0)
            {
                token.type = PROCEDURE;
            }
            else if (strcmp("program", token.id) == 0)
            {
                token.type = PROGRAM;
            }
            else if (strcmp("else", token.id) == 0)
            {
                token.type = ELSE;
            }
            else if (strcmp("for", token.id) == 0)
            {
                token.type = FOR;
            }
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